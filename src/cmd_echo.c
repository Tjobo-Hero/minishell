/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_echo.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/04 10:28:24 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/08 14:36:55 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_sign(t_mini *d, char *arg)
{
	t_env	*tmp;

	tmp = look_up(&arg[1], d->echo);
	if (arg[1] == '?')
	{
		ft_putnbr_fd(d->ret, d->fd);
		if (arg[2] != ' ')
			ft_putstr_fd(&arg[2], d->fd);
	}
	if (tmp != NULL)
		ft_putstr_fd(tmp->echo, d->fd);
}

int		**echo(t_mini *d)
{
	int	a;

	a = 1;
	if (ft_strncmp(d->args[a], "-n", 2) == 0)
		a++;
	while (d->args[a])
	{
		if (ft_strncmp(d->args[a], "$", 1) == 0)
			dollar_sign(d, d->args[a]);
		else
			ft_putstr_fd(d->args[a], d->fd);
		a++;
		if (d->args[a])
			ft_putchar_fd(' ', d->fd);
	}
	if (!d->args[1] || (d->args[1] && ft_strncmp(d->args[1], "-n", 3) != 0))
		ft_putchar_fd('\n', d->fd);
	return (0);
}
