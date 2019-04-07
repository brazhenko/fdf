/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supps2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 04:26:06 by lreznak-          #+#    #+#             */
/*   Updated: 2019/04/07 10:30:00 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		drawmap(t_fdf *fdf)
{
	int i;
	int j;

	j = -1;
	i = -1;
	unplot(fdf->img_data);
	while (++i < fdf->map->rows)
	{
		j = -1;
		while (++j < fdf->map->cols)
		{
			if (j != fdf->map->cols - 1)
				wu(fdf->img_data, fdf->map->dots[i][j],
				fdf->map->dots[i][j + 1]);
			if (i != fdf->map->rows - 1)
				wu(fdf->img_data, fdf->map->dots[i][j],
				fdf->map->dots[i + 1][j]);
		}
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	return (0);
}

int		key_press(int keycode, t_fdf *fdf)
{
	fdf->keyboard->pressed[keycode] = 1;
	if (keycode == 3)
	{
		mlx_loop_hook(fdf->mlx_ptr, tupa_chill, fdf);
		system("while :; do afplay music/bag-raiders-shooting-"
		"stars-official-video.mp3; done &");
		sleep(23);
		fdf->is_chill = 1;
	}
	else if (keycode == 2)
		map_twister_y(fdf->map, 1, MINIMUM_RADIAN);
	else if (keycode == 13)
		map_twister_x(fdf->map, 1, MINIMUM_RADIAN);
	else if (keycode == 14)
		map_twister_z(fdf->map, 1, MINIMUM_RADIAN);
	else if (keycode == 0)
		map_twister_y(fdf->map, 0, MINIMUM_RADIAN);
	else if (keycode == 1)
		map_twister_x(fdf->map, 0, MINIMUM_RADIAN);
	else if (keycode == 12)
		map_twister_z(fdf->map, 0, MINIMUM_RADIAN);
	if (keycode == 2 || keycode == 13 || keycode == 14 ||
		keycode == 0 || keycode == 1 || keycode == 12)
		drawmap(fdf);
	return (0);
}

int		key_release(int keycode, t_fdf *fdf)
{
	fdf->keyboard->pressed[keycode] = 0;
	return (0);
}

int		close1(t_fdf *fdf)
{
	(void)fdf;
	exit(0);
	return (0);
}

int		mouse_press(int button, int x, int y, t_fdf *fdf)
{
	fdf->mouse->pressed = button;
	fdf->mouse->x = x;
	fdf->mouse->y = y;
	if (fdf->mouse->pressed == 5)
	{
		map_scale(fdf->map, 1);
		drawmap(fdf);
	}
	else if (fdf->mouse->pressed == 4)
	{
		map_scale(fdf->map, 0);
		drawmap(fdf);
	}
	return (0);
}
