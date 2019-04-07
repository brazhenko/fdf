/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 23:40:02 by lreznak-          #+#    #+#             */
/*   Updated: 2019/04/07 05:39:21 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					file_exit(int code)
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

int					fdf_exit(void *data)
{
	ft_putstr_fd(CL, 1);
	init_window(0);
	set_keypress(0);
	system("kill $(ps | grep  'while :; do afplay music/"
		"bag-raiders-shooting-stars-official-video.mp3' | awk '{ print $1 }')");
	system("kill $(ps | grep \"afplay\" | awk '{ print $1 }')");
	exit(1);
}
