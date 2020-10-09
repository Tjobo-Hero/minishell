/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:03:42 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/09 14:00:06 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		**env(t_mini *d)
{
	t_env	*tmp;
	int		i;
	int		c;

	i = 0;
	c = 0;
	tmp = NULL;
	while (i < ECHO)
	{
		if (d->echo[i] != NULL)
		{
			tmp = d->echo[i];
			while (tmp && tmp->index != c)
				tmp = tmp->next;
		}
		if (tmp != NULL && tmp->index == c && tmp->set)
		{
			ft_printf("%s=", tmp->head);
			ft_printf("%s\n", tmp->echo);
			i = 0;
			c++;
		}
		else
			i++;
	}
	return (0);
}
