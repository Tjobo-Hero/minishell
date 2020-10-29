/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_echo.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:01:49 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:01:52 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			**cmd_echo(t_mini *d)
{
	int	a;

	a = 1;
	if (!d->args[1])
	{
		ft_putchar_fd('\n', d->fd);
		return (0);
	}
	if (ft_strncmp(d->args[a], "-n", 2) == 0)
		a++;
	while (d->args[a])
	{
		ft_write(d, d->args[a]);
		a++;
		if (d->args[a])
			ft_putchar_fd(' ', d->fd);
	}
	if ((d->args[1] && ft_strncmp(d->args[1], "-n", 3) != 0))
		ft_putchar_fd('\n', d->fd);
	return (0);
}
