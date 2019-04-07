/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 21:26:36 by lreznak-          #+#    #+#             */
/*   Updated: 2019/04/07 09:59:48 by wclayton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot(t_xy xy, char *data, double bs, t_pot rgb)
{
	if (xy.x < WIDTH && xy.y < HEIGHT && xy.y >= 0.0 && xy.x >= 0.0)
	{
		data[4 * (int)xy.x + 4 * WIDTH * (int)xy.y] = ceil((int)rgb.b * bs);
		data[4 * (int)xy.x + 4 * WIDTH * (int)xy.y + 1] = ceil((int)rgb.g * bs);
		data[4 * (int)xy.x + 4 * WIDTH * (int)xy.y + 2] = ceil((int)rgb.r * bs);
	}
}

void	unplot(char *data)
{
	int i;

	i = -1;
	while (++i < 4 * WIDTH * HEIGHT)
		data[i] = 0;
}

void	swap(double *a, double *b)
{
	double tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	iswap(unsigned char *a, unsigned char *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

double	ipart(double x)
{
	return (floor(x));
}
