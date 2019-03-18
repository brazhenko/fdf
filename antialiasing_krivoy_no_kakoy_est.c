#include "minilibx_macos/mlx.h"
#include <math.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_point
{
	double x;
	double y;
}				t_point;

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

void wu(char *data, t_point p1, t_point p2)
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

int main(void)
{
    void *mlx_ptr;
    void *win_ptr;
	char *img_data;
	void *img_ptr;
    int bpp;
	int sl;
	int endian;
	t_point p1;
	t_point p2;

	p1.x = 500;
	p1.y = 500;
	p2.x = 250;
	p2.y = 300;
    mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "123123");
	img_ptr = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	img_data = mlx_get_data_addr(img_ptr, &bpp, &sl, &endian);
	wu(img_data, p1, p2);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
//some hooks
	mlx_loop(mlx_ptr);
}