/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:03:42 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/02 18:57:32 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		**env(t_mini *d)
{
	int i;

	i = 0;
	while (d->env[i])
	{
		if (ft_strchr(d->env[i], '='))
			ft_printf("%s\n", d->env[i]);
		i++;
	}
	return (0);
}
