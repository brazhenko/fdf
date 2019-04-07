/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 21:08:13 by lreznak-          #+#    #+#             */
/*   Updated: 2019/04/07 04:41:22 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		tty_print(char *type, float data, char *str)
{
	struct winsize		winsz;
	char				buf[1024];

	ioctl(0, TIOCGWINSZ, &winsz);
	tgetent(buf, getenv("TERM"));
	if (ft_strequ(type, "angle_x"))
	{
		ft_putstr_fd(tgoto(tgetstr("cm", NULL), 5, 2), STDIN_FILENO);
		printf("%lf\n", data);
	}
	else if (ft_strequ(type, "angle_y"))
	{
		ft_putstr_fd(tgoto(tgetstr("cm", NULL), 5, 3), STDIN_FILENO);
		printf("%lf\n", data);
	}
	else if (ft_strequ(type, "angle_z"))
	{
		ft_putstr_fd(tgoto(tgetstr("cm", NULL), 5, 4), STDIN_FILENO);
		printf("%lf\n", data);
	}
	else if (ft_strequ(type, "log"))
	{
		ft_putstr_fd(tgoto(tgetstr("cm", NULL), 5, 10), STDIN_FILENO);
		ft_putstr_fd(str, STDIN_FILENO);
	}
}
