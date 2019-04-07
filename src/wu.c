/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wu.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wclayton <wclayton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 04:26:06 by lreznak-          #+#    #+#             */
/*   Updated: 2019/04/07 10:42:48 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	wu2(char *data, t_dot *p1, t_dot *p2, t_pxl *a)
{
	a->ypxl1 = ipart(a->yend);
	if (a->steep)
	{
		a->plc = (t_pot){(double)(p1->r), (double)(p1->g), (double)(p1->b)};
		plot((t_xy){a->ypxl1, a->xpxl1}, data, rfpart(a->yend) * a->xgap,
			a->plc);
		plot((t_xy){a->ypxl1 + 1, a->xpxl1}, data, fpart(a->yend) * a->xgap,
			a->plc);
	}
	else
	{
		a->plc = (t_pot){(double)(p1->r), (double)(p1->g), (double)(p1->b)};
		plot((t_xy){a->xpxl1, a->ypxl1}, data, rfpart(a->yend) * a->xgap,
			a->plc);
		plot((t_xy){a->xpxl1, a->ypxl1 + 1}, data, fpart(a->yend) * a->xgap,
			a->plc);
	}
	a->intery = a->yend + a->grad;
	a->xend = round(p2->x);
	a->yend = p2->y + a->grad * (a->xend - p2->x);
	a->xgap = fpart(p2->x + 0.5);
	a->xpxl2 = a->xend;
	a->ypxl2 = ipart(a->yend);
}

void	wu1(t_dot *p1, t_dot *p2, t_pxl *a)
{
	a->flag = 0;
	a->steep = (fabs(p2->y - p1->y) > fabs(p2->x - p1->x)) ? 1 : 0;
	if (a->steep)
	{
		swap(&(p1->x), &(p1->y));
		swap(&(p2->x), &(p2->y));
	}
	if (p1->x > p2->x)
	{
		swap(&(p1->x), &(p2->x));
		swap(&(p1->y), &(p2->y));
		iswap(&(p1->r), &(p2->r));
		iswap(&(p1->g), &(p2->g));
		iswap(&(p1->b), &(p2->b));
		a->flag = 1;
	}
	a->dx = p2->x - p1->x;
	a->dy = p2->y - p1->y;
	a->grad = a->dy / a->dx;
	if (a->dx == 0.0)
		a->grad = 1.0;
	a->xend = round(p1->x);
	a->yend = p1->y + a->grad * (a->xend - p1->x);
	a->xgap = rfpart(p1->x + 0.5);
	a->xpxl1 = a->xend;
}

void	wu3(char *data, t_dot *p1, t_dot *p2, t_pxl *a)
{
	while (a->i <= a->xpxl2)
	{
		a->plc =
			(t_pot){fabs(a->xpxl2 - a->i) / (a->xpxl2 - a->xpxl1) * p1->r +
				fabs(a->i - a->xpxl1) / (a->xpxl2 - a->xpxl1) * p2->r,
				fabs(a->xpxl2 - a->i) / (a->xpxl2 - a->xpxl1) * p1->g +
					fabs(a->i - a->xpxl1) / (a->xpxl2 - a->xpxl1) * p2->g,
				fabs(a->xpxl2 - a->i) / (a->xpxl2 - a->xpxl1) * p1->b +
					fabs(a->i - a->xpxl1) / (a->xpxl2 - a->xpxl1) * p2->b};
		plot((t_xy){ipart(a->intery), a->i}, data, rfpart(a->intery), a->plc);
		plot((t_xy){ipart(a->intery) + 1, a->i}, data, fpart(a->intery),
			a->plc);
		a->intery += a->grad;
		a->i++;
	}
}

void	wu4(char *data, t_dot *p1, t_dot *p2, t_pxl *a)
{
	while (a->i <= a->xpxl2)
	{
		a->plc =
			(t_pot){fabs(a->xpxl2 - a->i) / (a->xpxl2 - a->xpxl1) * p1->r +
				fabs(a->i - a->xpxl1) / (a->xpxl2 - a->xpxl1) * p2->r,
				fabs(a->xpxl2 - a->i) / (a->xpxl2 - a->xpxl1) * p1->g +
					fabs(a->i - a->xpxl1) / (a->xpxl2 - a->xpxl1) * p2->g,
				fabs(a->xpxl2 - a->i) / (a->xpxl2 - a->xpxl1) * p1->b +
					fabs(a->i - a->xpxl1) / (a->xpxl2 - a->xpxl1) * p2->b};
		plot((t_xy){a->i, ipart(a->intery)}, data, rfpart(a->intery), a->plc);
		plot((t_xy){a->i, ipart(a->intery) + 1}, data, fpart(a->intery),
			a->plc);
		a->intery += a->grad;
		a->i++;
	}
}

void	wu(char *data, t_dot p1, t_dot p2)
{
	t_pxl	a;

	wu1(&p1, &p2, &a);
	wu2(data, &p1, &p2, &a);
	if (a.steep)
	{
		a.plc = (t_pot){(double)p2.r, (double)p2.g, (double)p2.b};
		plot((t_xy){a.ypxl2, a.xpxl2}, data, rfpart(a.yend) * a.xgap, a.plc);
		plot((t_xy){a.ypxl2 + 1, a.xpxl2}, data, fpart(a.yend) * a.xgap, a.plc);
	}
	else
	{
		a.plc = (t_pot){(double)p2.r, (double)p2.g, (double)p2.b};
		plot((t_xy){a.xpxl2, a.ypxl2}, data, rfpart(a.yend) * a.xgap, a.plc);
		plot((t_xy){a.xpxl2, a.ypxl2 + 1}, data, fpart(a.yend) * a.xgap, a.plc);
	}
	a.i = (int)(a.xpxl1);
	if (a.steep)
		wu3(data, &p1, &p2, &a);
	else
		wu4(data, &p1, &p2, &a);
}
