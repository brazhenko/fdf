/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 21:26:36 by lreznak-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/04/04 23:11:38 by wclayton         ###   ########.fr       */
=======
/*   Updated: 2019/04/04 21:04:17 by lreznak-         ###   ########.fr       */
>>>>>>> 57fd8b430d689d345dea917cebd8c68b8d08c668
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

typedef struct 	s_dots
{
	int		cols;
	int		rows;
	t_dot	**dots;
}				t_dots;

typedef struct		s_mouse
{
	int				pressed;
	int				x;
	int				y;
}					t_mouse;

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
<<<<<<< HEAD
	int				projection;
=======
	int				is_chill;
>>>>>>> 57fd8b430d689d345dea917cebd8c68b8d08c668
}					t_fdf;

t_dots			*map_parser(const char *path);
int 			file_exit(int code);
void			wu(char *data, t_dot p1, t_dot p2);
int				pretty_terminal(int status);
void			map_twister_x(t_dots *map, int mode);
void			map_twister_y(t_dots *map, int mode);
void			map_twister_z(t_dots *map, int mode);
void			move_basis(t_dots *map, t_dot anchor);
void			remove_basis(t_dots *map, t_dot anchor);
t_dot			anchor(t_dots *map);
void			map_scale(t_dots *map, int mode);
void		tty_print(char *type, float data, char *str);




int				fdf_exit(void *data);

int		tupa_chill(t_fdf *fdf);


#endif
