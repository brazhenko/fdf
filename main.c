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

void plot(t_point i, char *data, double bs)
{
	printf("x y: %f %f\n", i.x, i.y);
	data[4 * (int)i.x + 4 * WIDTH * (int)i.y] = ceil(255 * (1 - bs));
	data[4 * (int)i.x + 4 * WIDTH * (int)i.y + 1] = ceil(255 * (1 - bs));
	data[4 * (int)i.x + 4 * WIDTH * (int)i.y + 2] = ceil(255 * (1 - bs));
}

void wu(char *data, t_point p1, t_point p2)
{
	double grad;
	double dst;
	double center1;
	int cx;
	double cy;
	double i = p1.x;
	double j = p1.y;
	t_point tp;
	double br;

	//proverka na steep
	grad = ((double)(p2.y - p1.y)/(double)(p2.x - p1.x));
	if (grad > 1)
		printf("%f\n", grad);
	tp.x = p1.x;
	tp.y = p1.y;
	//plot(tp, data, 1);
	if (grad <= 1)
	{
		j = 0;
		//QUARTER THREE)
		while(i < p2.x)
		{
			tp.x = i;
			printf("do modf %f\n", j);
			br = modf(j, &(tp.y));
			printf("posle %f\n", j);
			plot(tp, data, 1 - br);
			tp.y += 1;
			plot(tp, data, br);
			i++;
			j += grad;
		}
	}
	else
	{
		//steep
		i = 0;
		while (j < p2.y)
		{
			tp.y = j;
			printf("do modf %f\n", j);
			br = modf(i, &(tp.x));
			printf("posle %f\n", i);
			plot(tp, data, 1 - br);
			tp.x += 1;
			plot(tp, data, br);
			j++;
			i += grad;
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

	p1.x = 0;
	p1.y = 0;
	p2.x = 300;
	p2.y = 400;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "123123");
	img_ptr = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	img_data = mlx_get_data_addr(img_ptr, &bpp, &sl, &endian);
	wu(img_data, p1, p2);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	//some hooks
	mlx_loop(mlx_ptr);
}
