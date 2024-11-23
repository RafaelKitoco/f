#include "./headers/cub3d.h"



char	*create_spaced_line(char *line, int big_line)
{
	char	*ret;
	int		i;

	if (!line)
		return (NULL);
	ret = malloc(sizeof(char) * (big_line + 1));
	if (!ret)
		return (NULL);
	i = 0;
	// Copiar os caracteres da linha original
	while (line[i] && line[i] != '\n')
	{
		ret[i] = line[i];
		i++;
	}
	// Preencher o restante com espaços
	while (i < big_line)
	{
		ret[i] = ' ';
		i++;
	}
	// Finalizar a string
	ret[i] = '\0';
	return (ret);
}


void	make_map_rectangle(t_vars *vars)
{
	int		big_line;
	int		i;
	char	**matriz_dup;

	// Determinar o comprimento da maior linha na matriz do mapa
	big_line = ft_matriz_big_line(vars->map.worldMap);
	// Criar uma cópia da matriz original
	matriz_dup = ft_matrizdup(vars->map.worldMap);

	i = 0;
	while (matriz_dup[i])
	{
		// Liberar a linha atual do mapa
		free(vars->map.worldMap[i]);
		vars->map.worldMap[i] = NULL;

		// Substituir pela linha ajustada
		vars->map.worldMap[i] = create_spaced_line(matriz_dup[i], big_line - 1);
		i++;
	}

	// Liberar a matriz duplicada
	ft_free_matriz(matriz_dup);
}



bool is_empty_line(char *line)
{
    if (!line) // Verifica se a linha não é NULL
        return true;
    
    while (*line)
    {
        if (!ft_isspace(*line)) // Se encontrar um caractere não espaço
            return false;
        line++;
    }
    return true; // Retorna true se todos os caracteres forem espaços ou a linha for vazia
}



int find_starting_point(char **scene)
{
    int i = 0;
    int qt = 0;

    // Procurar elementos obrigatórios de configuração
    while (scene[i])
    {
        if (ft_strstr(scene[i], "NO ")
            || ft_strstr(scene[i], "SO ")
            || ft_strstr(scene[i], "WE ")
            || ft_strstr(scene[i], "EA ")
            || ft_strstr(scene[i], "F ")
            || ft_strstr(scene[i], "C "))
        {
            qt++;
        }
        i++;
        if (qt == 6) // Se todos os elementos forem encontrados
            break;
    }

    // Pular linhas vazias até encontrar o início do mapa
    while (scene[i] && is_empty_line(scene[i]))
        i++;

    // Verificar se o mapa começa após a configuração
    if (!scene[i] || is_empty_line(scene[i]))
    {
        ft_err_msg("Error: Map content missing after configuration.", true);
        return -1; // Retorna -1 se o mapa não for encontrado
    }

    return i;
}



void extract_map(t_vars *vars, char **scene)
{
    int start;

    // Localizar o índice inicial do mapa na configuração
    start = find_starting_point(scene);
    if (start == -1) // Se o índice não for encontrado
    {
        ft_err_msg("Error: Failed to find map starting point.", true);
        return;
    }

    // Duplicar a matriz do mapa a partir do índice inicial
    vars->map.worldMap = ft_matrizdup(&scene[start]);
    if (!vars->map.worldMap || vars->map.worldMap[0] == NULL)
    {
        ft_err_msg("Error: Failed to extract map or map is empty.", true);
        if (vars->map.worldMap)
            ft_free_matriz(vars->map.worldMap);
        vars->map.worldMap = NULL;
        return;
    }

    // Ajustar o mapa para ser retangular
    make_map_rectangle(vars);
}

bool	is_openble_file(char *path, char *extension, int ext_len)
{
	int		len;
	int		fd;
	char	*err_msg;

	if (!path || (extension && ext_len <= 0))
		return (ft_err_msg("Invalid arguments passed to is_openble_file!", false));

	len = ft_strlen(path);
	err_msg = ft_strjoin(path, " - Not a valid file!");
	if (!err_msg)
		return (ft_err_msg("Memory allocation failed!", false));

	// Verificar a extensão, se especificada
	if (extension)
	{
		if (len <= ext_len || ft_strncmp(extension, &path[len - ext_len], ext_len) != 0)
		{
			ft_err_msg(err_msg, false);
			return (free(err_msg), false);
		}
	}

	// Tentar abrir o arquivo
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_err_msg(err_msg, false);
		return (free(err_msg), false);
	}
	close(fd);
	return (free(err_msg), true);
}


bool is_element_missing(t_vars *vars)
{
    if (!vars->no_texture || !vars->so_texture || !vars->we_texture || !vars->ea_texture)
        return true;
    if (vars->floor_color[0] == -1 || vars->floor_color[1] == -1  || vars->floor_color[2] == -1 || vars->ceiling_color[0] == -1 || vars->ceiling_color[1] == -1 || vars->ceiling_color[2] == -1)
        return true;
    return false;
}

void	convert_color_system(t_vars *vars)
{
	// Converter os valores RGB do piso (floor_color) para hexadecimal
	vars->floor_color_hex = (vars->floor_color[0] << 16)
		| (vars->floor_color[1] << 8) | vars->floor_color[2];
	
	// Converter os valores RGB do teto (ceiling_color) para hexadecimal
	vars->ceiling_color_hex = (vars->ceiling_color[0] << 16)
		| (vars->ceiling_color[1] << 8) | vars->ceiling_color[2];
}


bool	is_rgb_valid(t_vars *vars)
{
    // Verificar se os valores RGB do piso estão corretos
    if (vars->floor_color[0] < 0 || vars->floor_color[0] > 255
        || vars->floor_color[1] < 0 || vars->floor_color[1] > 255
        || vars->floor_color[2] < 0 || vars->floor_color[2] > 255)
    {
        return (ft_err_msg("Floor color values must be between 0 and 255.", false));
    }

    // Verificar se os valores RGB do teto estão corretos
    if (vars->ceiling_color[0] < 0 || vars->ceiling_color[0] > 255
        || vars->ceiling_color[1] < 0 || vars->ceiling_color[1] > 255
        || vars->ceiling_color[2] < 0 || vars->ceiling_color[2] > 255)
    {
        return (ft_err_msg("Ceiling color values must be between 0 and 255.", false));
    }

    // Caso necessário, realizar conversões adicionais (ex.: para outro formato de cor)
    convert_color_system(vars);

    return (true); // Valores são válidos
}


bool is_spaced(char *str)
{
    int i = 0;

    if (!str)
        return false;

    // Pular espaços iniciais
    while (str[i] == ' ' || str[i] == '\t')
        i++;

    // Verificar espaços entre caracteres
    while (str[i])
    {
        // Se houver um espaço entre dois caracteres válidos (letras ou números), retorna true
        if ((ft_isalpha(str[i]) || ft_isdigit(str[i])) && (str[i + 1] == ' ' || str[i + 1] == '\t'))
            return true;
        i++;
    }
    
    return false;  // Se não houver espaços extras, retorna false
}


bool is_texture_and_color_valid(t_vars *vars, char **m)
{
    int i;
    int qt;

    i = 0;
    qt = 0;
    // Contando quantos elementos de texturas e cores existem no arquivo
    while (m[i])
    {
        if (m[i] && (ft_strstr(m[i], "NO ") || ft_strstr(m[i], "SO ") ||
                      ft_strstr(m[i], "WE ") || ft_strstr(m[i], "EA ") ||
                      ft_strstr(m[i], "F ") || ft_strstr(m[i], "C ")))
        {
            qt++;
        }
        i++;
    }

    // Verificando se o número de elementos é maior que o esperado
    if (qt > 6)
        return ft_err_msg("Duplicated Map Elements", false);

    // Verificando se há espaços indesejados entre os elementos
    if (is_spaced(vars->no_texture) || is_spaced(vars->so_texture) ||
        is_spaced(vars->we_texture) || is_spaced(vars->ea_texture))
    {
        return ft_err_msg("Invalid Map Element, space in between", false);
    }

    // Verificando se algum elemento está faltando
    if (is_element_missing(vars))
        return ft_err_msg("Missing map element", false);

    // Verificando se as cores RGB são válidas
    if (!is_rgb_valid(vars))
        return ft_err_msg("Invalid RGB color value", false);

    return true;
}


char **get_mapfile_info(char *file_path)
{
    char *line;
    char **map;
    int i;

    // Abrir o arquivo
    int fd = open(file_path, O_RDONLY);
    if (fd < 0)
        return (NULL);

    // Contar as linhas do arquivo
    int lines_count = ft_fd_lines_counter(file_path); // Assume que esta função está definida em outro lugar
    if (lines_count <= 0)
    {
        close(fd);
        return (NULL);
    }

    // Alocar memória para armazenar as linhas do mapa
    map = ft_calloc(sizeof(char *), lines_count + 1);
    if (!map)
    {
        close(fd);
        return (NULL);
    }

    // Ler o arquivo linha por linha
    i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        map[i] = ft_strdup(line);
        free(line);
        i++;
    }

    close(fd);
    return (map);
}

void	replace_tabs_to_space(char **cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub[i])
	{
		j = 0;
		while (cub[i][j] != '\0' && cub[i][j] != '\n')
		{
			if (cub[i][j] == '\t'){
				cub[i][j] = '0';
				printf("%c", cub[i][j]);
				}
			j ++;
		}
		printf("\n");
		i ++;
	}
}

/*void parse_color(char *color_str, int *color_array)
{
    int r = 0, g = 0, b = 0;
    char *ptr = color_str;

    // Ignorar espaços no início da string
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;

    // Parse da primeira cor (r)
    r = ft_atoi(ptr);

    // Avançar para o próximo número (após a vírgula)
    while (*ptr >= '0' && *ptr <= '9')
        ptr++;
    if (*ptr == ',') ptr++;

    // Ignorar espaços após a vírgula
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;

    // Parse da segunda cor (g)
    g = ft_atoi(ptr);

    // Avançar para o próximo número (após a vírgula)
    while (*ptr >= '0' && *ptr <= '9')
        ptr++;
    if (*ptr == ',') ptr++;

    // Ignorar espaços após a vírgula
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;

    // Parse da terceira cor (b)
    if (*ptr == ' ')
    	printf("Sou nullo! %c", *ptr);
    b = ft_atoi(ptr);

    // Atribuindo os valores no array de cores
    color_array[0] = r;
    color_array[1] = g;
    color_array[2] = b;
}*/

void parse_color(char *color_str, int *color_array)
{
    char **components;
    int i;

    // Ignorar espaços iniciais na string
    while (*color_str == ' ' || *color_str == '\t')
        color_str++;

    // Dividir a string por vírgulas
    components = ft_split(color_str, ',');
    if (!components)
    {
        ft_err_msg("Error: Memory allocation failed during color parsing.", true);
        return;
    }

    // Verificar se há exatamente 3 componentes (R, G, B)
    for (i = 0; components[i] != NULL; i++)
    {
        if (i > 2)
            break; // Mais de 3 componentes encontrados
    }
    if (i != 3)
    {
        ft_free_matriz(components);
        ft_err_msg("Error: Invalid color format, expected 3 values (R, G, B).", false);
        return;
    }

    // Validar cada componente (após a vírgula deve ser um número válido)
    for (i = 0; i < 3; i++)
    {
        char *ptr = components[i];
        // Ignorar espaços antes e depois do número
        while (*ptr == ' ' || *ptr == '\t')
            ptr++;
        if (!*ptr || ft_isdigit(*ptr) == 0)
        {
            ft_free_matriz(components);
            ft_err_msg("Error: Color components must be valid integers.", false);
            return;
        }
        while (*ptr && ft_isdigit(*ptr))
            ptr++;
        while (*ptr == ' ' || *ptr == '\t')
            ptr++;
        /*if (*ptr) // Se sobrar algo, não é um número puro
        {
            ft_free_matriz(components);
            ft_err_msg("Error: Invalid characters found in color values.", false);
            return;
        }*/
    }

    // Converter os valores para inteiros e verificar a validade
    int r = ft_atoi(components[0]);
    int g = ft_atoi(components[1]);
    int b = ft_atoi(components[2]);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        ft_free_matriz(components);
        ft_err_msg("Error: Color values must be between 0 and 255.", false);
        return;
    }

    // Atribuir os valores ao array de cores
    color_array[0] = r;
    color_array[1] = g;
    color_array[2] = b;

    ft_free_matriz(components); // Liberar a memória alocada para os componentes
}



char	*get_element_info(char *line)
{
	int		j;
	int		i;
	char	*extracted;
	char	*trim;

	j = 0;
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i ++;
	while (ft_isalpha(line[i]))
		i ++;
	if (line[i] == ' ' || line[i] == '\t')
	{
		while (line[i] == ' ' || line[i] == '\t')
			i ++;
	}
	j = i;
	while (line[i] != '\0' && line[i] != '\n' && line[i] != '\t')
		i ++;
	extracted = ft_substr(line, j, i - j);
	trim = ft_strtrim(extracted, " ");
	free(extracted);
	return (trim);
}

void get_texture_and_color(t_vars *vars, char **lines)
{
    int i = 0;
    
    while (lines[i])
    {
        // Verifica se a linha contém "NO " (Norte) e se a textura não foi definida
        if (lines[i] && ft_strstr(lines[i], "NO ") && !vars->no_texture)
        {
            vars->no_texture = get_element_info(lines[i]);
            printf("No: %s\n", vars->no_texture);
        }
        // Verifica se a linha contém "SO " (Sul) e se a textura não foi definida
        else if (lines[i] && ft_strstr(lines[i], "SO ") && !vars->so_texture)
        {
            vars->so_texture = get_element_info(lines[i]);
            printf("So: %s\n", vars->so_texture);
        }
        // Verifica se a linha contém "WE " (Oeste) e se a textura não foi definida
        else if (lines[i] && ft_strstr(lines[i], "WE ") && !vars->we_texture)
        {
            vars->we_texture = get_element_info(lines[i]);
            printf("We: %s\n", vars->we_texture);
        }
        // Verifica se a linha contém "EA " (Leste) e se a textura não foi definida
        else if (lines[i] && ft_strstr(lines[i], "EA ") && !vars->ea_texture)
        {
            vars->ea_texture = get_element_info(lines[i]);
        }
        // Verifica se a linha contém "F " (Cor do Piso) e se ainda não foi definida
        else if (lines[i] && ft_strstr(lines[i], "F ") && vars->floor_color[0] == -1)
        {
            parse_color(&lines[i][2], vars->floor_color);
        }
        // Verifica se a linha contém "C " (Cor do Teto) e se ainda não foi definida
        else if (lines[i] && ft_strstr(lines[i], "C ") && vars->ceiling_color[0] == -1)
        {
            parse_color(&lines[i][2], vars->ceiling_color);
        }
        i++;
    }
}

/*
static void calculate_map_size(char **lines, int *width, int *height) {
    *height = 0;
    *width = 0;
    for (int i = 0; lines[i] != NULL; i++) {
        if (first_line(lines[i])) {
            (*height)++;
            int line_length = strlen(lines[i]);
            if (line_length > *width) {
                *width = line_length;
            }
        }
    }
}


int	find_firts(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

static void parse_map(char **lines, t_vars *vars, int start) {
    vars->map.worldMap = malloc(vars->map.height * sizeof(int *));
    if (!vars->map.worldMap) {
        fprintf(stderr, "Error: Failed to allocate memory for map.\n");
        exit(EXIT_FAILURE);
    }

    int playerCount = 0;
    for (int i = 0; i < vars->map.height; i++) {
        vars->map.worldMap[i] = malloc(vars->map.width * sizeof(int));
        if (!vars->map.worldMap[i]) {
            fprintf(stderr, "Error: Failed to allocate memory for map row.\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < vars->map.width; j++) {
            if (lines[start + i][j] == ' ') {
                vars->map.worldMap[i][j] = -1;
            } else if (lines[start + i][j] == '1') {
                vars->map.worldMap[i][j] = 1;
            } else if (lines[start + i][j] == '0') {
                vars->map.worldMap[i][j] = 0;
            } else if (find_firts(lines[start + i][j])) {
                vars->player.posX = i + 0.5;
                vars->player.posY = j + 0.5;
                if (lines[start + i][j] == 'N') {
                    vars->player.dirX = -1; 
                    vars->player.dirY = 0; 
                    vars->player.planeX = 0; 
                    vars->player.planeY = 0.66;
                } else if (lines[start + i][j] == 'S') {
                    vars->player.dirX = 1;
                    vars->player.dirY = 0;
                    vars->player.planeX = 0;
                    vars->player.planeY = -0.66;
                } else if (lines[start + i][j] == 'E') {
                    vars->player.dirX = 0;
                    vars->player.dirY = 1;
                    vars->player.planeX = 0.66;
                    vars->player.planeY = 0;
                } else if (lines[start + i][j] == 'W') {
                    vars->player.dirX = 0;
                    vars->player.dirY = -1;
                    vars->player.planeX = -0.66;
                    vars->player.planeY = 0;
                }
                // Certifique-se de não marcar a célula como 2, mantenha-a como '0' para permitir a movimentação
                vars->map.worldMap[i][j] = 0;
                playerCount++;
            }
        }
    }

    if (playerCount != 1) {
        fprintf(stderr, "Error: Mapa deve ter exatamente uma posição inicial do jogador.\n");
        exit(EXIT_FAILURE);
    }
}*/


/*static int is_map_closed(t_vars *vars)
{ 
    for (int i = 0; i < vars->map.height; i++) 
    { 
        for (int j = 0; j < vars->map.width; j++)
        { 
            if (vars->map.worldMap[i][j] == 0 || strchr("NSEW", vars->map.worldMap[i][j]))
            { 
                if (i == 0 || i == vars->map.height - 1 || j == 0 || j == vars->map.width - 1 || vars->map.worldMap[i-1][j] == ' ' || vars->map.worldMap[i+1][j] == ' ' || vars->map.worldMap[i][j-1] == ' ' || vars->map.worldMap[i][j+1] == ' ')
                {
                    return 0;
                } 
            }
        }
    } 
    return 1; 
}*/

/*
static int is_map_closed(t_vars *vars) {
    // Verificação horizontal
    for (int i = 0; i < vars->map.height; i++) {
        if (vars->map.worldMap[i][0] != 1 || vars->map.worldMap[i][vars->map.width - 1] != 1) {
            printf("%d %d", vars->map.worldMap[i][vars->map.width - 1], i);
            return 0;
        }
    }

    // Verificação vertical
    for (int j = 0; j < vars->map.width; j++) {
        if (vars->map.worldMap[0][j] != 1 || vars->map.worldMap[vars->map.height - 1][j] != 1) {
            return 0;
        }
    }
    
    return 1;
}*/

int parse_config(char *file_path, t_vars *vars) {

    char **lines = get_mapfile_info(file_path);
    if (!lines) {
        perror("Error reading lines from file");
        exit(EXIT_FAILURE);
    }
    replace_tabs_to_space(lines);
    get_texture_and_color(vars, lines);
    if (!is_texture_and_color_valid(vars, lines)
		|| !is_openble_file(vars->no_texture, ".xpm", 4)
		|| !is_openble_file(vars->so_texture, ".xpm", 4)
		|| !is_openble_file(vars->we_texture, ".xpm", 4)
		|| !is_openble_file(vars->ea_texture, ".xpm", 4))
		{
			ft_free_matriz(lines);
			return (EXIT_FAILURE);
		}
    
    extract_map(vars, lines);
    if (!is_map_valid(vars))
    {
    	ft_free_matriz(lines);
    	return (EXIT_FAILURE);
    }
    //calculate_map_size(lines, &vars->map.width, &vars->map.height);
    
    //parse_map(lines, vars, i);

    /*if (!is_map_closed(vars)) {
        fprintf(stderr, "Error: Mapa não está cercado por paredes.\n");
        exit(EXIT_FAILURE);
    }*/

    ft_free_matriz(lines);
    //free(line);
    printf("Eu cheguei\n");
    return (EXIT_SUCCESS);
}
