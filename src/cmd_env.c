/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:02:17 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:02:20 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(t_mini *d, t_env *tmp)
{
	ft_putstr_fd(tmp->head, d->fd);
	ft_write(d, "=");
	ft_putstr_fd(tmp->echo, d->fd);
	ft_write(d, "\n");
}

int			**cmd_env(t_mini *d)
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
			print_env(d, tmp);
			i = 0;
			c++;
		}
		else
			i++;
	}
	return (0);
}
