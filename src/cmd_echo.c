/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_echo.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/04 10:28:24 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/07 14:21:32 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_sign(t_mini *d, char *arg)
{
	t_env	*tmp;

	tmp = look_up(&arg[1], d->echo);
	if (tmp != NULL)
		ft_printf("ECHO: %s\n", tmp->echo);
}

void	echo_n_option(t_mini *d)
{
	(void)d;
	printf("TEST\n");
}

int		**echo(t_mini *d)
{
	int	a;

	a = 1;
	if (ft_strncmp(d->args[a], "-n", 2) == 0)
		echo_n_option(d);
	while (d->args[a])
	{
		if (ft_strncmp(d->args[a], "$", 1) == 0)
			dollar_sign(d, d->args[a]);
		a++;
	}
	return (0);
}