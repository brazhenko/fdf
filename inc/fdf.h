/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 21:26:36 by lreznak-          #+#    #+#             */
/*   Updated: 2019/03/16 06:02:20 by wclayton         ###   ########.fr       */
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

# define DIR_ERROR			1
# define FILE_ERROR			2
# define ERROR_BIG_FILE		3

# define WIDTH 800
# define HEIGHT 600

# define MINIMUM_RADIAN		0.001

typedef struct	s_dot
{
	double 	x;
	double 	y;
	double 	z;
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

t_dots			*map_parser(const char *path);
int 			file_exit(int code);
void wu(char *data, t_dot p1, t_dot p2);
int			pretty_terminal(int status);
void			map_twister_x(t_dots *map);
void			map_twister_y(t_dots *map);
void			map_twister_z(t_dots *map);



#endif
