/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_coloring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 09:57:16 by lreznak-          #+#    #+#             */
/*   Updated: 2019/04/07 09:58:26 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float				auto_color_sigmoid(float arg)
{
	return (1 / (1 + exp(-10 * (arg - 0.5))));
}

void				auto_coloring(t_dots *map)
{
	int		i;
	int		j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			map->dots[i][j].r = map->dots[i][j].color ? map->dots[i][j].r :
					(unsigned char)(auto_color_sigmoid((float)
					(map->dots[i][j].z - map->minh) /
					(float)(map->maxh - map->minh)) * 0x4c);
			map->dots[i][j].g = map->dots[i][j].color ? map->dots[i][j].g :
					(unsigned char)((-auto_color_sigmoid((float)
					(map->dots[i][j].z - map->minh) /
					(float)(map->maxh - map->minh)) + 1) * 0x4c);
			map->dots[i][j].z *= 10;
		}
	}
}
