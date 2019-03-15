/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 21:26:36 by lreznak-          #+#    #+#             */
/*   Updated: 2019/03/15 20:47:12 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* PASS */
# include <sys/stat.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>

# define DIR_ERROR			1
# define FILE_ERROR			2
# define ERROR_BIG_FILE		3

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

t_dots			*map_parser(const char *path);


#endif
