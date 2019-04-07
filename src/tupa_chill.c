/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tupa_chill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 20:00:18 by lreznak-          #+#    #+#             */
/*   Updated: 2019/04/07 10:29:22 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		tupa_chill(t_fdf *fdf)
{
	sleep(10);
	usleep(40000);
	if (fdf->is_chill)
	{
		map_chill_twister(fdf->map, 1);
		map_scale(fdf->map, 0);
	}
	drawmap(fdf);
	return (0);
}
