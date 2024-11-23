/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 03:25:01 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/23 03:26:27 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void init_textr_struct(t_vars *vars)
{
    vars->no_texture = NULL;
    vars->so_texture = NULL;
    vars->we_texture = NULL;
    vars->ea_texture = NULL;
}
void	init_color_struct(t_vars *vars)
{
	vars->floor_color[0] = -1;
	vars->floor_color[1] = -1;
	vars->floor_color[2] = -1;
	vars->ceiling_color[0] = -1;
	vars->ceiling_color[1] = -1;
	vars->ceiling_color[2] = -1;
	
}
void init_map_struct(t_vars *vars)
{
    vars->map.worldMap = NULL;
    vars->map.width = 0;
    vars->map.height = 0;
}



int init_game_struct(t_vars *vars)
{
    ft_bzero(vars, sizeof(t_vars));  // Zera a estrutura principal

    // Alocação de memória para o mapa
    vars->map.worldMap = malloc(sizeof(char *) * vars->map.height);
    if (!vars->map.worldMap)
        return (ft_err_msg("Error allocating map worldMap", EXIT_FAILURE));

    // Inicializa o mapa
    init_map_struct(vars);
    init_color_struct(vars);

    // Aloca memória para o jogador
    vars->player.posX = 0.0;
    vars->player.posY = 0.0;
    //vars->player.dirX = 1.0;  // Direção inicial para a direita
    //vars->player.dirY = 0.0;  // Direção inicial para a direita
    vars->player.planeX = 0.0;
    vars->player.planeY = 0.66;  // Plane inicial (perpendicular à direção do jogador)

    // Inicializa as texturas
    init_textr_struct(vars);

    return (EXIT_SUCCESS);
}

