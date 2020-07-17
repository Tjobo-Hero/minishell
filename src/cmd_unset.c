/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_unset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 14:55:19 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/17 15:28:28 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_alpha_index(t_env **echo, int index, int alpha)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (i < ECHO)
	{
		if (echo[i])
		{
			tmp = echo[i];
			while (tmp)
			{
				if (tmp->index > index)
					tmp->index--;
				if (tmp->alpha > alpha)
					tmp->alpha--;
				tmp = tmp->next;
			}
		}
		i++;
	}
}

int		**unset(t_mini *d)
{
	t_env	*tmp;
	int		a;
	int		index_cmp;
	int		alpha_cmp;

	a = 1;
	while (d->args[a])
	{
		tmp = look_up(d->args[a], d->echo);
		if (tmp)
		{
			index_cmp = tmp->index;
			alpha_cmp = tmp->alpha;
			delete_lst(d->args[a], d->echo);
			set_alpha_index(d->echo, index_cmp, alpha_cmp);
			d->index--;
		}
		if (d->args[a][ft_strlen(d->args[a]) - 1] == '=')
			ft_printf("unset: %s: invalid parameter name\n", d->args[a]);
		a++;
	}
	return (0);
}
