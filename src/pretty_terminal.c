/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pretty_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreznak- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 04:26:06 by lreznak-          #+#    #+#             */
/*   Updated: 2019/03/16 04:42:41 by lreznak-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			pretty_terminal(int status)
{

	struct ttysize  	ts;
	int 				i = 0, j = 0;
	char buf[1024];

	set_keypress(1);
	init_window(1);
	tgetent(buf, getenv("TERM"));
	ioctl(0, TIOCGSIZE, &ts);
	ft_putstr_fd(tgetstr("so", NULL), 0);
	while (i < ts.ts_lines)
	{
		ft_putstr_fd(tgoto(CM, 0, i), STDIN_FILENO);
		ft_putstr(" ");
		ft_putstr_fd(tgoto(CM, ts.ts_cols - 1, i), STDIN_FILENO);
		ft_putstr(" ");
		i++;
	}
	while (j < ts.ts_cols)
	{
		ft_putstr_fd(tgoto(CM, j, 0), STDIN_FILENO);
		ft_putstr(" ");
		ft_putstr_fd(tgoto(CM, j, ts.ts_lines - 1), STDIN_FILENO);
		ft_putstr(" ");
		j++;
	}
	ft_putstr_fd(tgetstr("se", NULL), 0);
	return (0);
}