/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:03:42 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/11 09:12:59 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		**env(t_mini *d)
{
	int i;

	i = 0;
	while (d->env[i] != NULL && d->env[i]->set)
	{
		ft_printf("%s\n", d->env[i]->list);
		i++;
	}
	return (0);
}
