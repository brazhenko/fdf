/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 21:08:13 by lreznak-          #+#    #+#             */
/*   Updated: 2019/04/03 23:32:09 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		tty_print(char *type, float data)
{
	struct winsize winsz;
	char	buf[1024];

	init_window(1);
	set_keypress(1);

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
}