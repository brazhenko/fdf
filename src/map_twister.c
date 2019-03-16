/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_twister.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 05:46:33 by lreznak-          #+#    #+#             */
/*   Updated: 2019/03/16 05:59:41 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			map_twister_x(t_dots *map)
{
	int 		i = 0, j = 0;
	double 		tmp;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			/* map->dots[i][j].x = x; */
			tmp = map->dots[i][j].y;
			map->dots[i][j].y = y * cos(MINIMUM_RADIAN) + map->dots[i][j].z * sin(MINIMUM_RADIAN);
			map->dots[i][j].z = = -tmp * sin(MINIMUM_RADIAN) + z * cos(MINIMUM_RADIAN);
			j++;
		}
		i++;
	}
}

void			map_twister_y(t_dots *map)
{
	int 		i = 0, j = 0;
	double 		tmp;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			tmp = map->dots[i][j].x;
			map->dots[i][j].x = x * cos(MINIMUM_RADIAN) + map->dots[i][j].z * sin(MINIMUM_RADIAN);
			/* map->dots[i][j].x = x; */
			map->dots[i][j].z = -tmp * sin(MINIMUM_RADIAN) + map->dots[i][j].z * cos(MINIMUM_RADIAN);
			j++;
		}
		i++;
	}
}

void			map_twister_z(t_dots *map)
{
	int 		i = 0, j = 0;
	double 		tmp;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			tmp = map->dots[i][j].x;
			map->dots[i][j].x = x * cos(MINIMUM_RADIAN) - map->dots[i][j].y * sin(MINIMUM_RADIAN);
			map->dots[i][j].y = -tmp * sin(MINIMUM_RADIAN) + map->dots[i][j].y * cos(MINIMUM_RADIAN);
			/* map->dots[i][j].z = z; */
			j++;
		}
		i++;
	}
}