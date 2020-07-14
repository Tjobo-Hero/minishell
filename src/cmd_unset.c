/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_unset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 14:55:19 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/13 09:01:04 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_from_list(char *arg, t_env **env)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (env[c] != NULL)
		c++;
	while (ft_strncmp(arg, env[i]->head, ft_strlen(arg)))
		i++;
	// while (i < c)
	// {
	// 	clear_list()
	// }
}

int		**unset(t_mini *d)
{
	t_env	*tmp;
	int		a;

	a = 1;
	while (d->args[a])
	{
		tmp = look_up(d->args[a], d->echo);
		if (tmp)
		{
			delete_lst(d->args[a], d->echo);
			remove_from_list(d->args[a], d->env);
		}
		a++;
	}
	return (0);
}
