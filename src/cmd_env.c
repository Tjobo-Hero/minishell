/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:03:42 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/15 09:42:03 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		**env(t_mini *d)
{
	t_env	*tmp;
	int 	i;
	int 	c;

	i = 0;
	c = 0;
	while (i < ECHO)
	{
		if (d->echo[i] != NULL)
		{
			tmp = d->echo[i];
			while (tmp && tmp->index != c)
				tmp = tmp->next;
		}
		if (tmp != NULL && tmp->index == c)
		{
			ft_printf("%s\n", tmp->list);
			i = 0;
			c++;
		}
		else
			i++;
	}
	return (0);
}
