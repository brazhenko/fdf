/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supps1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 04:26:06 by wclayton          #+#    #+#             */
/*   Updated: 2019/04/07 09:29:46 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move_basis(t_dots *map)
{
	int i;
	int j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			map->dots[i][j].x -= map->anc.x;
			map->dots[i][j].y -= map->anc.y;
			map->dots[i][j].z -= map->anc.z;
		}
	}
}

void	remove_basis(t_dots *map)
{
	int i;
	int j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			map->dots[i][j].x += map->anc.x;
			map->dots[i][j].y += map->anc.y;
			map->dots[i][j].z += map->anc.z;
		}
	}
}

double	round(double x)
{
	return (ipart(0.5 + x));
}

double	fpart(double x)
{
	return (x - floor(x));
}

double	rfpart(double x)
{
	return (1 - fpart(x));
}
