/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 01:17:22 by lreznak-          #+#    #+#             */
/*   Updated: 2019/04/01 20:46:13 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"


int 			file_exit(int code)
{
	if (code == DIR_ERROR)
	{
		ft_putstr("Do not attach directory!\n");
		exit(EXIT_FAILURE);
	}
	else if (code == FILE_ERROR)
	{
		ft_putstr("There is no such file!\n");
		exit(EXIT_FAILURE);
	}
	else if (code == ERROR_BIG_FILE)
	{
		ft_putstr("File is too big!!\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

static int 			ptrlen(char **ptr)
{
	int		i = 0;
	while (ptr[i])
	{
		i++;
	}
	return (i);
}
static int 			ptrptrlen(char **ptr)
{
	int		i = 0;
	while (ptr[i])
	{
		i++;
	}
	return (i);
}
t_dots			*map_parser(const char *path)
{
	t_dots			*map;
	struct stat		f;
	int				fd, i = 0;
	unsigned long long		sz;
	char 					m[3276222];
	char				**bsn_split;
	char 				***ws_split = malloc(sizeof(char **) * 100000);
	int 				max_len = 0;
	int 				strcount = 0;

	if ((fd = open(path, O_RDONLY)) > 0)
	{
		stat(path, &f);
		if (S_ISDIR(f.st_mode))
		{
			file_exit(DIR_ERROR);
		}
	}
	else
	{
		file_exit(FILE_ERROR);
	}
	if (f.st_size < 0b1111111111111111111)
	{
		read(fd, m, f.st_size);
	}
	else
		file_exit(ERROR_BIG_FILE);
	bsn_split = ft_strsplit(m, '\n');
	while (*bsn_split)
	{
		ws_split[i] = ft_strsplit(*bsn_split, ' ');
		max_len = ptrlen(ws_split[i]) > max_len ? ptrlen(ws_split[i]) : max_len;
		bsn_split++;
		i++;
	}
	strcount = i; //ptrptrlen(bsn_split);
	ws_split[i] = NULL;
	map = (t_dots *)malloc(sizeof(t_dots));
	map->dots = (t_dot **)malloc(sizeof(t_dot *) * (i + 1));
	map->dots[i] = NULL;
	for (register int j = 0 ; j < i ; ++j)
	{
		map->dots[j] = (t_dot *)malloc(sizeof(t_dot) * max_len);
	}

	char	**onedot_with_color;
	for (register int k = 0 ; k < 100000; ++k)
	{
		if (!ws_split[k])
			break ;
		for (int m = 0; m < max_len; ++m)
		{
			if (!ws_split[k][m])
				break ;
			onedot_with_color = ft_strsplit(ws_split[k][m], ',');
			map->dots[k][m].z = 15 * atoi(onedot_with_color[0]/*ws_split[k][m]*/);
			map->dots[k][m].x = m * (WIDTH / max_len);
			map->dots[k][m].y = k * (HEIGHT / i);
			map->dots[k][m].color = onedot_with_color[1] ? ft_atoi_base(onedot_with_color[1] + 2, 16) : 0xFFFFFF;
			map->dots[k][m].r = 0b11111111 & (map->dots[k][m].color >> 16);
			map->dots[k][m].g = 0b11111111 & (map->dots[k][m].color >> 8);
			map->dots[k][m].b = 0b11111111 & map->dots[k][m].color;
		}
	}
	for (int l = 0; l < i; ++l)
	{
		for (int j = 0; j < max_len; ++j)
		{
			printf("%f ", map->dots[l][j].z);
		}
		printf("\n");
	}
	printf("\n");

	for (int l = 0; l < i; ++l)
	{
		for (int j = 0; j < max_len; ++j)
		{
			printf("%f ", map->dots[l][j].x);
		}
		printf("\n");
	}
	printf("\n");

	for (int l = 0; l < i; ++l)
	{
		for (int j = 0; j < max_len; ++j)
		{
			printf("%f ", map->dots[l][j].y);
		}
		printf("\n");
	}
	printf("%d\n", map->rows = i);
	printf("%d\n", map->cols = max_len);
	return (map);
}
