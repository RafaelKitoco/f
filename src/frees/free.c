/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 01:08:41 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/23 01:09:12 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void free_vars(t_vars *vars)
{
    if (vars)
    {
        // Liberar texturas (se alocadas)
        if (vars->no_texture)
            free(vars->no_texture);
        if (vars->so_texture)
            free(vars->so_texture);
        if (vars->we_texture)
            free(vars->we_texture);
        if (vars->ea_texture)
            free(vars->ea_texture);

        // Liberar mapa (se alocado)
        if (vars->map.worldMap)
        {
            int i = 0;
            while (vars->map.worldMap[i])
            {
                free(vars->map.worldMap[i]);
                i++;
            }
            free(vars->map.worldMap);
        }

        // Liberar estrutura principal
        free(vars);
    }
}

// Libera a memória e define o ponteiro como NULL
void ft_free(void *ptr)
{
    if (ptr) {
        free(ptr);
        ptr = NULL; // Garante que o ponteiro não fique "pendurado"
    }
}

