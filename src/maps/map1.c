/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:51:25 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/23 17:37:39 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

bool	are_all_lines_valid(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->map.worldMap[i])  // Acessando o mapa armazenado em worldMap
	{
		if (is_empty_line(vars->map.worldMap[i]))  // Verificando se a linha está vazia
			return (ft_err_msg("Invalid line on map!", false));  // Erro se linha estiver vazia
		i ++;
	}
	return (true);  // Retorna true se todas as linhas forem válidas
}

bool	is_line_horizontal_valid(char *line)
{
	int	i;

	i = 0;
	// Ignora espaços no início da linha
	while (line[i] == ' ')
		i++;

	// Verifica se o primeiro caractere não é '1', indicando uma linha inválida
	if (line[i] && line[i] != '1')
		return (ft_err_msg("Map horizontal line invalid", false));

	// Verifica cada caractere na linha
	while (line[i])
	{
		// Se encontrar um dos caracteres 'N', 'S', 'E', 'W' (indicando a posição do jogador)
		if (ft_strchr("NSEW", line[i]))
		{
			// Verifica se há espaços após o caractere do jogador, o que é inválido
			if (line[i + 1] && line[i + 1] == ' ')
				return (ft_err_msg("Invalid Player Indication", false));
			i++;  // Avança para o próximo caractere
			continue;
		}

		// Verifica se o caractere é válido ('0', '1', ' ').
		// No caso de '0' ou ' ' não serem seguidos por '1' ou '0' corretamente, marca como erro
		if (ft_strchr("01 ", line[i]))
		{
			if ((line[i] == ' ' && line[i + 1] && line[i + 1] == '0') ||
				(line[i] == '0' && line[i + 1] && line[i + 1] == ' '))
				return (ft_err_msg("Map horizontal line invalid", false));
		}
		i++;  // Avança para o próximo caractere
	}

	return (true);  // Retorna true se a linha for válida
}

bool	is_line_vertical_valid(char **map)
{
	int	line;
	int	chars;
	int	qt_lines;
	int	qt_chars;

	line = 0;
	chars = 0;
	qt_chars = ft_matriz_big_line(map);
	qt_lines = ft_matrizlen(map);
	while (chars < qt_chars)
	{
		if (line + 1 < qt_lines && (map[line][chars] == ' '
			&& map[line + 1][chars] == ' '))
		{
			line ++ ;
			continue ;
		}
		if (line + 1 < qt_lines && ((map[line][chars] == ' '
				&& map[line + 1][chars] == '0') || (map[line][chars] == '0'
					&& map[line + 1][chars] == ' ')))
			return (ft_err_msg("Invalid Map", false));
		if (is_line_vertical_valid_aux(&line, &chars, &qt_lines, &qt_chars))
			break ;
	}
	return (true);
}

/**
 * @attention Auxiliar to is_line_vertical_valid()
 * Just because of norminette. Used to break the loop.
*/
int	is_line_vertical_valid_aux(int *l, int *ch, int *qt_l, int *qt_ch)
{
	if ((*l) == (*qt_l) && (*ch) == (*qt_ch))
		return (EXIT_FAILURE);
	(*l)++;
	if ((*l) == (*qt_l))
	{
		(*l) = 0;
		(*ch)++;
	}
	return (EXIT_SUCCESS);
}

bool	is_first_last_valid(char **map)
{
	int	last_line;
	int	j;

	last_line = ft_matrizlen(map) - 1;
	j = 0;
	while (jump_spaces(map[0][j], &j, 0))
		j ++;
	if (ft_strchr(&map[0][j], '0'))
		return (ft_err_msg("First map line invalid!", false));
	j = 0;
	while (jump_spaces(map[last_line][j], &j, 0))
		j ++;
	if (ft_strchr(&map[last_line][j], '0'))
		return (ft_err_msg("Last map line invalid!", false));
	return (true);
}

