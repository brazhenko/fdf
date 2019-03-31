#include "fdf.h"




//void swap(t_point p1)

void	move_basis(t_dots *map, t_dot anchor)
{
	int i;
	int j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			map->dots[i][j].x -= anchor.x;
			map->dots[i][j].y -= anchor.y;
			map->dots[i][j].z -= anchor.z;
		}
	}
}

void	remove_basis(t_dots *map, t_dot anchor)
{
	int i;
	int j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			map->dots[i][j].x += anchor.x;
			map->dots[i][j].y += anchor.y;
			map->dots[i][j].z += anchor.z;
		}
	}
}

void plot(double x, double y, char *data, double bs)
{

	if (x < WIDTH && y < HEIGHT && y >=0.0 && x >= 0.0)
	{
		data[4 * (int)x + 4 * WIDTH * (int)y] = ceil(255 * bs);
		data[4 * (int)x + 4 * WIDTH * (int)y + 1] = ceil(255 * bs);
		data[4 * (int)x + 4 * WIDTH * (int)y + 2] = ceil(255 * bs);
	}
}

void unplot(char *data)
{
	int i = -1;
	while (++i < 4 * WIDTH * HEIGHT)
		data[i] = 0;
}

void swap(double *a, double *b)
{
	double tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

double ipart(double x)
{
	return (floor(x));
}

double round(double x)
{
	return (ipart(0.5 + x));
}

double fpart(double x)
{
	return (x - floor(x));
}

double rfpart(double x)
{
	return(1 - fpart(x));
}



void wu(char *data, t_dot p1, t_dot p2)
{
	double dx;
	double dy;
	double grad;
	double xend;
	double yend;
	double xgap;
	double xpxl1;
	double ypxl1;
	double xpxl2;
	double ypxl2;
	int steep;
	int i;
	double intery;
	
	steep = (fabs(p2.y - p1.y) > fabs(p2.x - p1.x)) ? 1 : 0;
	if (steep)
	{
		swap(&(p1.x), &(p1.y));
		swap(&(p2.x), &(p2.y));
	}
	if (p1.x > p2.x)
	{
		swap(&(p1.x), &(p2.x));
		swap(&(p1.y), &(p2.y));
	}
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	grad = dy / dx;
	if (dx == 0.0)
		grad = 1.0;

	xend = round(p1.x);
	yend = p1.y + grad * (xend - p1.x);
	xgap = rfpart(p1.x + 0.5);
	xpxl1 = xend;
	ypxl1 = ipart(yend);
	if (steep)
	{
		plot(ypxl1, xpxl1, data, rfpart(yend) * xgap);
		plot(ypxl1 + 1, xpxl1, data, fpart(yend) * xgap);
	}
	else
	{
		plot(xpxl1, ypxl1, data, rfpart(yend) * xgap);
		plot(xpxl1, ypxl1 + 1, data, fpart(yend) * xgap);
	}
	intery = yend + grad;

	xend = round(p2.x);
	yend = p2.y + grad * (xend - p2.x);
	xgap = fpart(p2.x + 0.5);
	xpxl2 = xend;
	ypxl2 = ipart(yend);
	if (steep)
	{
		plot(ypxl2, xpxl2, data, rfpart(yend) * xgap);
		plot(ypxl2 + 1, xpxl2, data, fpart(yend) * xgap);
	}
	else
	{
		plot(xpxl2, ypxl2, data, rfpart(yend) * xgap);
		plot(xpxl2, ypxl2 + 1, data, fpart(yend) * xgap);
	}

	i = (int)(xpxl1);
	if (steep)
	{
		while (i <= xpxl2)
		{
			plot(ipart(intery), i, data, rfpart(intery));
			plot(ipart(intery) + 1, i, data, fpart(intery));
			intery += grad;
			i++;
		}
	}
	else
	{
		while (i <= xpxl2)
		{
			plot(i, ipart(intery), data, rfpart(intery));
			plot(i, ipart(intery) + 1, data, fpart(intery));
			intery += grad;
			i++;
		}
	}
}

void drawmap(t_fdf *fdf)
{
	int i = -1;
	int j = -1;

	unplot(fdf->img_data);
	while (++i < fdf->map->rows)
	{
		j = -1;
		while (++j < fdf->map->cols)
		{
			if (j != fdf->map->cols - 1)
				wu(fdf->img_data, fdf->map->dots[i][j], fdf->map->dots[i][j + 1]);
			if (i != fdf->map->rows - 1)
				wu(fdf->img_data, fdf->map->dots[i][j], fdf->map->dots[i + 1][j]);
		}
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}

int key_press(int keycode, t_fdf *fdf)
{
	fdf->keyboard->pressed[keycode] = 1;
	int i = -1;
	int j = -1;
	
	if (keycode == 2)
	{
		map_twister_y(fdf->map, 1);
		drawmap(fdf);
	}
	else if (keycode == 13)
	{
		map_twister_x(fdf->map, 1);
		drawmap(fdf);
	}
	else if (keycode == 14)
	{
		map_twister_z(fdf->map, 1);
		drawmap(fdf);
	}
	else if (keycode == 0)
	{
		map_twister_y(fdf->map, 0);
		drawmap(fdf);
	}
	else if (keycode == 1)
	{
		map_twister_x(fdf->map, 0);
		drawmap(fdf);
	}
	else if (keycode == 12)
	{
		map_twister_z(fdf->map, 0);
		drawmap(fdf);
	}
	return(0);
}

int key_release(int keycode, t_fdf *fdf)
{
	fdf->keyboard->pressed[keycode] = 0;
	return (0);
}

int close1(t_fdf *fdf)
{
    (void)fdf;
    exit(0);
    return (0);
}

double dist(t_dot p1, t_dot p2)
{
	return(sqrt(pow(2, p1.x - p2.x) + pow(2, p1.y - p2.y) + pow(2, p1.z - p2.z)));
}

int mouse_press(int button, int x, int y, t_fdf *fdf)
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



int mouse_release(int button, int x, int y, t_fdf *fdf)
{
	fdf->mouse->pressed = 0;
	//printf("mr b %d x %d y %d\n", button, x, y);
	return (0);
}

int mouse_move(int x, int y, t_fdf *fdf)
{
	int i = -1, j;
	if (fdf->mouse->pressed == 1)
	{
		while (++i < fdf->map->rows)
		{
			j = -1;
			while(++j < fdf->map->cols)
			{
				fdf->map->dots[i][j].x += (x - fdf->mouse->x);
				fdf->map->dots[i][j].y += (y - fdf->mouse->y);
			}
		}
	}
	fdf->mouse->x = x;
	fdf->mouse->y = y;
	drawmap(fdf);
	//printf("mm x %d y %d\n", x, y);
	return (0);
}

t_dot	anchor(t_dots *map)
{
	t_dot anc;

	anc.x = (map->dots[map->rows - 1][0].x + map->dots[0][map->cols - 1].x) / 2;
	anc.y = (map->dots[map->rows - 1][0].y + map->dots[0][map->cols - 1].y) / 2;
	anc.z = map->dots[map->rows / 2][map->cols / 2].z / 2;
	return (anc);
}

int main(int ac, char *av[])
{
	int i = -1, j = -1;
	t_fdf	*fdf;

	if (!(fdf = (t_fdf*)malloc(sizeof(t_fdf))))
		exit(0);
	fdf->mouse = (t_mouse*)malloc(sizeof(t_mouse));
	fdf->mouse->pressed = -1;
	fdf->mouse->x = -1;
	fdf->mouse->y = -1;

	if (!(fdf->keyboard = (t_keyboard*)malloc(sizeof(t_keyboard))))
		exit(0);
	i = -1;
	while (++i < 256)
		fdf->keyboard->pressed[i] = 0;
	i = -1;
	if (ac > 1)
		fdf->map = map_parser(av[1]);
	else
		file_exit(FILE_ERROR);

    fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "123123");
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	fdf->img_data = mlx_get_data_addr(fdf->img_ptr, &(fdf->bpp), &(fdf->sl), &(fdf->endian));

	while (++i < fdf->map->rows)
	{
		j = -1;
		while (++j < fdf->map->cols)
		{
			if (j != fdf->map->cols - 1)
				wu(fdf->img_data, fdf->map->dots[i][j], fdf->map->dots[i][j + 1]);
			if (i != fdf->map->rows - 1)
				wu(fdf->img_data, fdf->map->dots[i][j], fdf->map->dots[i + 1][j]);
		}
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	//some hooks
	mlx_hook(fdf->win_ptr, 2, 0, key_press, fdf);
	mlx_hook(fdf->win_ptr, 3, 0, key_release, fdf);
	mlx_hook(fdf->win_ptr, 4, 0, mouse_press, fdf);
	mlx_hook(fdf->win_ptr, 5, 0, mouse_release, fdf);
	mlx_hook(fdf->win_ptr, 6, 0, mouse_move, fdf);
	mlx_hook(fdf->win_ptr, 17, 0, close, fdf);
	mlx_loop(fdf->mlx_ptr);
}
