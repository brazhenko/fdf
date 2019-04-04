/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 23:40:02 by lreznak-          #+#    #+#             */
/*   Updated: 2019/04/03 23:48:36 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_exit(void *data)
{
	ft_putstr_fd(CL, 1);
	init_window(0);
	set_keypress(0);
	exit(1);
}