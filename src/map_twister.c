/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_twister.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 05:46:33 by lreznak-          #+#    #+#             */
/*   Updated: 2019/03/17 17:08:16 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			map_twister_x(t_dots *map, int mode)
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
			map->dots[i][j].y = map->dots[i][j].y * cos((mode == 1) ? MINIMUM_RADIAN : -MINIMUM_RADIAN) + map->dots[i][j].z * sin((mode == 1) ? MINIMUM_RADIAN : -MINIMUM_RADIAN);
			map->dots[i][j].z = -tmp * sin((mode == 1) ? MINIMUM_RADIAN : -MINIMUM_RADIAN) + map->dots[i][j].z * cos((mode == 1) ? MINIMUM_RADIAN : -MINIMUM_RADIAN);
			j++;
		}
		i++;
	}
}

void			map_twister_y(t_dots *map, int mode)
{
	int 		i = 0, j = 0;
	double 		tmp;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			tmp = map->dots[i][j].x;
			map->dots[i][j].x = map->dots[i][j].x * cos((mode == 1) ? MINIMUM_RADIAN : -MINIMUM_RADIAN) + map->dots[i][j].z * sin((mode == 1) ? MINIMUM_RADIAN : -MINIMUM_RADIAN);
			/* map->dots[i][j].x = x; */
			map->dots[i][j].z = -tmp * sin((mode == 1) ? MINIMUM_RADIAN : -MINIMUM_RADIAN) + map->dots[i][j].z * cos((mode == 1) ? MINIMUM_RADIAN : -MINIMUM_RADIAN);
			j++;
		}
		i++;
	}
}

void			map_twister_z(t_dots *map, int mode)
{
	int 		i = 0, j = 0;
	double 		tmp;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			tmp = map->dots[i][j].x;
			map->dots[i][j].x = map->dots[i][j].x * cos((mode == 1) ? MINIMUM_RADIAN : -MINIMUM_RADIAN) - map->dots[i][j].y * sin((mode == 1) ? MINIMUM_RADIAN : -MINIMUM_RADIAN);
			map->dots[i][j].y = tmp * sin((mode == 1) ? MINIMUM_RADIAN : -MINIMUM_RADIAN) + map->dots[i][j].y * cos((mode == 1) ? MINIMUM_RADIAN : -MINIMUM_RADIAN);
			/* map->dots[i][j].z = z; */
			j++;
		}
		i++;
	}
}