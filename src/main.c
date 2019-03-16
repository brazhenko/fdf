#include "fdf.h"




//void swap(t_point p1)

void plot(double x, double y, char *data, double bs)
{
	printf("x y: %f %f\n", x, y);
	data[4 * (int)x + 4 * WIDTH * (int)y] = ceil(255 * bs);
	data[4 * (int)x + 4 * WIDTH * (int)y + 1] = ceil(255 * bs);
	data[4 * (int)x + 4 * WIDTH * (int)y + 2] = ceil(255 * bs);
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

void swap(double *a, double *b)
{
	double tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int key_press(int keykode, void *param)
{
	printf("kp cc %d\n", keykode);
	return(0);
}

int close1(void *param)
{
    (void)param;
    exit(0);
    return (0);
}

int key_release(int keycode, void *param)
{
	printf("kr cc %d\n", keycode);
	return (0);
}

int mouse_press(int button, int x, int y, t_mouse *mouse)
{
	mouse->pressed = 1;
	printf("mp b %d x %d y %d mmp %d\n", button, x, y, mouse->pressed);
	return (0);
}

int mouse_release(int button, int x, int y, void *param)
{
	printf("mr b %d x %d y %d\n", button, x, y);
	return (0);
}

int mouse_move(int x, int y, void *param)
{
	printf("mm x %d y %d\n", x, y);
	return (0);
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

	i = (int)(xpxl1 + 1);
	if (steep)
	{
		while (i <= xpxl2 - 1)
		{
			plot(ipart(intery), i, data, rfpart(intery));
			plot(ipart(intery) + 1, i, data, fpart(intery));
			intery += grad;
			i++;
		}
	}
	else
	{
		while (i <= xpxl2 - 1)
		{
			plot(i, ipart(intery), data, rfpart(intery));
			plot(i, ipart(intery) + 1, data, fpart(intery));
			intery += grad;
			i++;
		}
	}
}

int main(int ac, char *av[])
{
    void *mlx_ptr;
    void *win_ptr;
	char *img_data;
	void *img_ptr;
    int bpp;
	int sl;
	int endian;
	t_dots *map;
	int i = -1, j = -1;
	t_mouse *mouse;

	mouse = (t_mouse*)malloc(sizeof(t_mouse));
	mouse->pressed = 0;
	mouse->x = -1;
	mouse->y = -1;
	if (ac > 1)
		map = map_parser(av[1]);
	else
		file_exit(FILE_ERROR);
	
	pretty_terminal(1);
	sleep(3);
    mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "123123");
	img_ptr = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	img_data = mlx_get_data_addr(img_ptr, &bpp, &sl, &endian);

	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			if (j != map->cols - 1)			
				wu(img_data, map->dots[i][j], map->dots[i][j + 1]);
			if (i != map->rows - 1)
				wu(img_data, map->dots[i][j], map->dots[i + 1][j]);			
		}
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
//some hooks
mlx_hook(win_ptr, 2, 0, key_press, NULL);
mlx_hook(win_ptr, 3, 0, key_release, NULL);
mlx_hook(win_ptr, 4, 0, mouse_press, mouse);
mlx_hook(win_ptr, 5, 0, mouse_release, mouse);
mlx_hook(win_ptr, 6, 0, mouse_move, NULL);
mlx_hook(win_ptr, 17, 0, close, NULL);
mlx_loop(mlx_ptr);
}
