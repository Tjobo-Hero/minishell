/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_echo.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/04 10:28:24 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/04 15:41:59 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_sign(t_mini *d)
{
	t_env	*tmp;

	tmp = look_up(&d->args[1][1], d->echo);
	if (tmp != NULL)
		ft_printf("ECHO: %s\n", tmp->echo);
}

int		**echo(t_mini *d)
{
	if (ft_strncmp(d->args[1], "$", 1) == 0)
		dollar_sign(d);
	return (0);
}