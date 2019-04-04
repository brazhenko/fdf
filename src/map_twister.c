/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_twister.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 05:46:33 by lreznak-          #+#    #+#             */
/*   Updated: 2019/04/04 22:43:43 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			map_twister_x(t_dots *map, int mode)
{
	int 		i = 0, j = 0;
	double 		tmp;
	t_dot		anc;

	anc = anchor(map);
	move_basis(map, anc);
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
	remove_basis(map, anc);
}

void			map_scale(t_dots *map, int mode)
{
	int			i, j;
	t_dot		anc;

	anc = anchor(map);
	move_basis(map, anc);
	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			/* map->dots[i][j].x = x; */
			map->dots[i][j].x *= (mode == 1) ? 1.1 : 0.9;
			map->dots[i][j].y *= (mode == 1) ? 1.1 : 0.9;
			map->dots[i][j].z *= (mode == 1) ? 1.1 : 0.9;
		}
	}
	remove_basis(map, anc);
}

void			map_twister_y(t_dots *map, int mode)
{
	int 		i = 0, j = 0;
	double 		tmp;
	t_dot		anc;

	anc = anchor(map);
	move_basis(map, anc);
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
	remove_basis(map, anc);

}

void			map_chill_twister(t_dots *map, int mode)
{
	int 		i = 0, j = 0;
	double 		tmp;
	t_dot		anc;

	anc = anchor(map);
	move_basis(map, anc);
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			tmp = map->dots[i][j].x;

			map->dots[i][j].x = map->dots[i][j].x * cos((mode == 1) ? 0.05 : -0.05) + map->dots[i][j].z * sin((mode == 1) ? 0.05 : -0.05);
			/* map->dots[i][j].x = x; */
			map->dots[i][j].z = -tmp * sin((mode == 1) ? 0.05 : -0.05) + map->dots[i][j].z * cos((mode == 1) ? 0.05 : -0.05);
			j++;
		}
		i++;
	}
	remove_basis(map, anc);

	anc = anchor(map);
	move_basis(map, anc);
	i = -1;
	usleep(10000);
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{

			/* map->dots[i][j].x = x; */
			map->dots[i][j].x *= (mode == 1) ? 1.1 : 0.99999;
			map->dots[i][j].y *= (mode == 1) ? 1.1 : 0.99999;
			map->dots[i][j].z *= (mode == 1) ? 1.1 : 0.99999;
		}
	}
	remove_basis(map, anc);
}

void			map_twister_z(t_dots *map, int mode)
{
	int 		i = 0, j = 0;
	double 		tmp;
	t_dot		anc;

	anc = anchor(map);
	move_basis(map, anc);
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
	remove_basis(map, anc);
}