/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 19:50:17 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/03 10:38:45 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_lowest(t_env **echo, t_env *new, int cmp)
{
	t_env	*tmp;
	int		i;
	int		c;

	i = 0;
	c = 0;
	tmp = NULL;
	while (i < ECHO)
	{
		if (echo[i])
		{
			tmp = echo[i];
			while (tmp)
			{
				c = ft_strncmp(new->head, tmp->head, ft_strlen(new->head));
				if (c < 0 && tmp->alpha < cmp)
					cmp = tmp->alpha;
				if (c == 0 && cmp > tmp->alpha)
					cmp = tmp->alpha;
				tmp = tmp->next;
			}
		}
		i++;
	}
	return (cmp);
}

void	set_alpha(t_env **echo, int cmp)
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
				if (tmp->alpha >= cmp)
					tmp->alpha++;
				tmp = tmp->next;
			}
		}
		i++;
	}
}

void	new_list(t_mini *d)
{
	set_env(&d->list[d->index], d->nw_list, d->index);
	d->list[d->index].alpha = find_lowest(d->echo, &d->list[d->index],
	d->index);
	set_alpha(d->echo, d->list[d->index].alpha);
	hash_table_insert_index(d, &d->list[d->index], d->echo,
	hash_echo(d->list[d->index].head, ECHO));
	d->index++;
}
