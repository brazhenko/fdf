/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 01:17:22 by lreznak-          #+#    #+#             */
/*   Updated: 2019/04/07 09:12:46 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static int			ptrlen(char **ptr)
{
	int		i;

	i = 0;
	while (ptr[i])
	{
		i++;
	}
	return (i);
}

static int			ptrptrlen(char **ptr)
{
	int		i;

	i = 0;
	while (ptr[i])
	{
		i++;
	}
	return (i);
}

float				auto_color_sigmoid(float arg)
{
	return (1 / (1 + exp(-10 * (arg - 0.5))));
}

static void			auto_coloring(t_dots *map)
{
	int		i;
	int		j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			map->dots[i][j].r = map->dots[i][j].color ? map->dots[i][j].r :
			(unsigned char)(auto_color_sigmoid((float)
			(map->dots[i][j].z - map->minh) /
			(float)(map->maxh - map->minh)) * 0x4c);
			map->dots[i][j].g = map->dots[i][j].color ? map->dots[i][j].g :
			(unsigned char)((-auto_color_sigmoid((float)
			(map->dots[i][j].z - map->minh) /
			(float)(map->maxh - map->minh)) + 1) * 0x4c);
			map->dots[i][j].z *= 10;
		}
	}
}

static void			init_map(t_dots *map, char ***ws_split)
{
	int			i;
	int			j;
	char		**one_dot_with_color;

	i = -1;
	while (ws_split[++i])
	{
		j = -1;
		map->dots[i] = (t_dot *)malloc(sizeof(t_dot) * map->cols);
		while (ws_split[i][++j])
		{
			one_dot_with_color = ft_strsplit(ws_split[i][j], ',');
			map->dots[i][j] = (t_dot){j * (WIDTH / map->cols), i * (HEIGHT /
				map->rows), ft_atoi(one_dot_with_color[0]),
				one_dot_with_color[1] ? ft_atoi_base(one_dot_with_color[1] + 2,
				16) : 0, 0b11111111 & (map->dots[i][j].color >> 16),
				0b11111111 & (map->dots[i][j].color >> 8),
				0b11111111 & map->dots[i][j].color};
			map->maxh = map->dots[i][j].z > map->maxh ?
					map->dots[i][j].z : map->maxh;
			map->minh = map->dots[i][j].z < map->minh ?
					map->dots[i][j].z : map->minh;
		}
	}
	auto_coloring(map);
}

char				*map_reader(const char *path)
{
	int					fd;
	char				m[3276222];
	struct stat			f;

	if ((fd = open(path, O_RDONLY)) > 0)
	{
		stat(path, &f);
		if (S_ISDIR(f.st_mode))
			file_exit(DIR_ERROR);
	}
	else
		file_exit(FILE_ERROR);
	if (f.st_size < 0xfffffffffffffff)
		read(fd, m, f.st_size);
	else
		file_exit(ERROR_BIG_FILE);
	return (m);
}

void				anching(t_dots *map)
{
	map->angle.x = 0;
	map->angle.y = 0;
	map->angle.z = 0;
	map->ani.z = map->minh;
	map->anz.z = map->maxh;
	map->ani.y = map->dots[0][0].y;
	map->ani.x = map->dots[0][0].x;
	map->anz.y = map->dots[0][0].y;
	map->anz.x = map->dots[0][0].x;
	map->anx.z = map->minh;
	map->anx.y = map->dots[0][map->cols - 1].y;
	map->anx.x = map->dots[0][map->cols - 1].x;
	map->any.z = map->minh;
	map->any.y = map->dots[map->rows - 1][0].y;
	map->any.x = map->dots[map->rows - 1][0].x;
	map->anc.x = (map->anx.x + map->any.x + map->anz.x - map->ani.x) / 2;
	map->anc.y = (map->anx.y + map->any.y + map->anz.y - map->ani.y) / 2;
	map->anc.z = (map->anx.z + map->any.z + map->anz.z - map->ani.z) / 2;
}

t_dots				*map_parser(const char *path)
{
	t_dots		*map;
	char		**bsn_split;
	char		**ws_split[100000];

	map = (t_dots *)malloc(sizeof(t_dots));
	bsn_split = ft_strsplit(map_reader(path), '\n');
	map->maxh = -2147483648;
	map->minh = 2147483647;
	map->cols = 0;
	map->rows = -1;
	while (bsn_split[++(map->rows)])
	{
		ws_split[map->rows] = ft_strsplit(bsn_split[map->rows], ' ');
		map->cols = ptrlen(ws_split[map->rows]) > map->cols ?
						ptrlen(ws_split[map->rows]) : map->cols;
	}
	ws_split[map->rows] = NULL;
	map->dots = (t_dot **)malloc(sizeof(t_dot *) * (map->rows + 1));
	map->dots[map->rows] = NULL;
	map->rows = map->rows;
	init_map(map, ws_split);
	anching(map);
	return (map);
}
