/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 23:40:02 by lreznak-          #+#    #+#             */
/*   Updated: 2019/04/07 04:41:47 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_exit(void *data)
{
	ft_putstr_fd(CL, 1);
	init_window(0);
	set_keypress(0);
	system("kill $(ps | grep  'while :; do afplay music/"
		"bag-raiders-shooting-stars-official-video.mp3' | awk '{ print $1 }')");
	system("kill $(ps | grep \"afplay\" | awk '{ print $1 }')");
	exit(1);
}
