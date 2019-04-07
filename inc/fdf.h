/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 21:26:36 by lreznak-          #+#    #+#             */
/*   Updated: 2019/04/07 10:03:19 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* PASS */
# include <sys/stat.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <math.h>
# include <stdio.h>
# include "../minilibx_macos/mlx.h"
# include "ft_select.h"
# include "libft.h"
# include <sys/ioctl.h>

# define DIR_ERROR			1
# define FILE_ERROR			2
# define ERROR_BIG_FILE		3

# define WIDTH 1600
# define HEIGHT 1200

# define MINIMUM_RADIAN		0.2

# define CL (tgetstr("cl", NULL))

typedef struct	s_dot
{
	double 	x;
	double 	y;
	double 	z;
	int color;
	unsigned char r;
	unsigned char g;
	unsigned  char b;
}				t_dot;

typedef struct	s_pot
{
	double 	r;
	double 	g;
	double 	b;
}				t_pot;

typedef struct	s_pxl
{
	double	dx;
	double	dy;
	double	grad;
	double	xend;
	double	yend;
	double	xgap;
	double	xpxl1;
	double	ypxl1;
	double	xpxl2;
	double	ypxl2;
	int		steep;
	int		i;
	double	intery;
	int		flag;
	t_pot	plc;
}				t_pxl;

typedef struct 	s_dots
{
	t_dot	angle;
	int		cols;
	int		rows;
	int		maxh;
	int		minh;
	t_dot	anc;
	t_dot	**dots;
	t_dot	ani;
	t_dot	anx;
	t_dot	any;
	t_dot	anz;
}				t_dots;

typedef struct		s_mouse
{
	int				pressed;
	int				x;
	int				y;
}					t_mouse;

typedef struct		s_xy
{
	double			x;
	double			y;
}					t_xy;

typedef struct		s_keyboard
{
	int				pressed[256];
}					t_keyboard;


typedef struct		s_fdf
{
	t_mouse			*mouse;
	t_keyboard		*keyboard;
	t_dots			*map;
	void			*mlx_ptr;
    void			*win_ptr;
	char			*img_data;
	void			*img_ptr;
	int				bpp;
	int				sl;
	int				endian;
	int				projection;
	int				is_chill;
}					t_fdf;

t_dots			*map_parser(const char *path);
int 			file_exit(int code);
void			wu(char *data, t_dot p1, t_dot p2);
int				pretty_terminal(int status);
void			map_twister_x(t_dots *map, int mode, double angle);
void			map_twister_y(t_dots *map, int mode, double angle);
void			map_twister_z(t_dots *map, int mode, double angle);
void			move_basis(t_dots *map);
void			remove_basis(t_dots *map);
t_dot			anchor(t_dots *map);
void			map_scale(t_dots *map, int mode);
void			tty_print(char *type, float data, char *str);
void			plot(t_xy xy, char *data, double bs, t_pot rgb);
void			unplot(char *data);
void			swap(double *a, double *b);
void			iswap(unsigned char *a, unsigned char *b);
double			ipart(double x);
double			round(double x);
double			fpart(double x);
double			rfpart(double x);
int		drawmap(t_fdf *fdf);
int		key_press(int keycode, t_fdf *fdf);
int		key_release(int keycode, t_fdf *fdf);
int		mouse_press(int button, int x, int y, t_fdf *fdf);
int		close1(t_fdf *fdf);




int				fdf_exit(void *data);
int				file_exit(int code);

int				tupa_chill(t_fdf *fdf);


#endif
