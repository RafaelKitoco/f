/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:17:42 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/23 16:58:29 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

bool is_map_valid(t_vars *vars)
{
    char **m_copy;

    // Verificar se a matriz do mapa não está vazia
    if (vars->map.worldMap == NULL || vars->map.worldMap[0] == NULL)
        return (ft_err_msg("Error: Empty map.", false));

    // Criar uma cópia da matriz para validações
    m_copy = ft_matrizdup(vars->map.worldMap);
    if (!have_onlyvalid_ch(vars) || !are_all_lines_valid(vars)
        || !is_player_valid(vars) || !is_map_closed(vars->map.worldMap))
    {
        ft_free_matriz(m_copy); // Liberar a memória se a validação falhar
        return false;
    }

    // Definir as dimensões do mapa
    vars->map.height = ft_matrizlen(vars->map.worldMap);
    vars->map.width = ft_matriz_big_line(vars->map.worldMap);

    // Liberar a memória da cópia da matriz
    ft_free_matriz(m_copy);

    return true;
}

bool have_onlyvalid_ch(t_vars *vars)
{
    int i;
    int j;

    // Iterar por todas as linhas do mapa
    i = -1;
    while (vars->map.worldMap[++ i])
    {
        // Iterar por todos os caracteres de cada linha
        j = -1;
        while (vars->map.worldMap[i][++ j])
        {
            // Verificar se o caractere é inválido
            if (!ft_strchr("01NSEW ", vars->map.worldMap[i][j]))
            {
                ft_err_msg("Invalid character in map!", false);
                return (false); // Se encontrar um caractere inválido, retorna falso
            }
        }
    }
    return true; // Todos os caracteres são válidos
}

bool is_player_valid(t_vars *vars)
{
    int i;
    int j;
    int qt;

    i = -1;
    j = 0;
    qt = 0;

    // Itera por todas as linhas do mapa
    while (vars->map.worldMap[++i])
    {
        j = -1;
        // Itera por todos os caracteres em cada linha
        while (vars->map.worldMap[i][++j])
        {
            // Verifica se o caractere é um dos símbolos do jogador (N, S, E, W)
            if (ft_strchr("NSEW", vars->map.worldMap[i][j]))
            {
                qt++;
                // Atualiza a posição do jogador (X, Y) e a direção
                vars->player.posX = j + 0.5;  // Posição centralizada
                vars->player.posY = i + 0.5;  // Posição centralizada
                if (vars->map.worldMap[i][j] == 'N')
		{
                    vars->player.dirX = -1.0;
		    vars->player.dirY = 0.0;
		}
                else if (vars->map.worldMap[i][j] == 'S')
		{
                    vars->player.dirX = 1.0;
		    vars->player.dirY = 0.0;
		}
                else if (vars->map.worldMap[i][j] == 'E')
		{
                   vars->player.dirX = 0.0;
		   vars->player.dirY = 1.0;
		}
                else if (vars->map.worldMap[i][j] == 'W')
		{
                    vars->player.dirX = 0.0;
		    vars->player.dirY = -1.0;
		}
            }
        }
    }

    // Verifica se existe exatamente 1 jogador
    if (qt != 1)
        return ft_err_msg("Invalid player on map", false);

    return true;
}

bool is_map_closed(char **map)
{
    int i;

    if (!is_last_column_closed(map) || !is_line_vertical_valid(map) || !is_first_last_valid(map))
        return false;

    i = 0;
    while (map[i])
    {
        if (!is_line_horizontal_valid(map[i]))
            return false;
        i++;
    }
    return true;
}

bool is_last_column_closed(char **map)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = ft_strlen(map[i]) - 1; // Começa na última posição válida da linha
        while (j >= 0)
        {
            if (jump_spaces(map[i][j], &j, 1)) // Ignorar espaços
                continue;
            if (map[i][j] != '1') // Verifica se o caractere final válido é '1'
                return (ft_err_msg("Map last column invalid!", false));
            else
                break; // Sai do loop se encontrar '1'
        }
        i++;
    }
    return (true);
}

