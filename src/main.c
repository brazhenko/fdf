/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 04:26:06 by lreznak-          #+#    #+#             */
/*   Updated: 2019/04/07 10:00:06 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_release(int button, int x, int y, t_fdf *fdf)
{
	fdf->mouse->pressed = 0;
	return (0);
}

int		mouse_move(int x, int y, t_fdf *fdf)
{
	int i;
	int j;

	if (fdf->mouse->pressed == 1)
	{
		i = -1;
		while (++i < fdf->map->rows)
		{
			j = -1;
			while (++j < fdf->map->cols)
			{
				fdf->map->dots[i][j].x += (x - fdf->mouse->x);
				fdf->map->dots[i][j].y += (y - fdf->mouse->y);
			}
		}
		fdf->map->anc.x += (x - fdf->mouse->x);
		fdf->map->anc.y += (y - fdf->mouse->y);
		drawmap(fdf);
	}
	fdf->mouse->x = x;
	fdf->mouse->y = y;
	return (0);
}

void	mlg(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "AIM");
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	fdf->img_data = mlx_get_data_addr(fdf->img_ptr, &(fdf->bpp),
											&(fdf->sl), &(fdf->endian));
	drawmap(fdf);
	mlx_hook(fdf->win_ptr, 17, 0, close1, fdf);
	mlx_hook(fdf->win_ptr, 2, 0, key_press, fdf);
	mlx_hook(fdf->win_ptr, 3, 0, key_release, fdf);
	mlx_hook(fdf->win_ptr, 4, 0, mouse_press, fdf);
	mlx_hook(fdf->win_ptr, 5, 0, mouse_release, fdf);
	mlx_hook(fdf->win_ptr, 6, 0, mouse_move, fdf);
	mlx_loop(fdf->mlx_ptr);
}

int		main(int ac, char *av[])
{
	int			i;
	t_fdf		*fdf;

	signal(SIGINT, fdf_exit);
	if (!(fdf = (t_fdf*)malloc(sizeof(t_fdf))))
		exit(0);
	if (!(fdf->mouse = (t_mouse*)malloc(sizeof(t_mouse))))
		exit(0);
	fdf->mouse->pressed = -1;
	fdf->mouse->x = -1;
	fdf->mouse->y = -1;
	if (!(fdf->keyboard = (t_keyboard*)malloc(sizeof(t_keyboard))))
		exit(0);
	i = -1;
	while (++i < 256)
		fdf->keyboard->pressed[i] = 0;
	if (ac > 1)
		fdf->map = map_parser(av[1]);
	else
		file_exit(FILE_ERROR);
	mlg(fdf);
}
