/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:47:57 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/23 17:48:20 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

bool	jump_spaces(char ch, int *j, int backwards)
{
	if (ch == ' ' && !backwards)
	{
		(*j)++;
		return (true);
	}
	if (ch == ' ' && backwards)
	{
		(*j)--;
		return (true);
	}
	return (false);
}
