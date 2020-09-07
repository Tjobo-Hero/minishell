/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_unset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 14:55:19 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/07 13:32:27 by rbraaksm      ########   odam.nl         */
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

	a = 1;
	while (d->args[a])
	{
		clear_new(d);
		check_arg(d, d->args[a]);
		if ((ft_isalpha_str(d->nw_tmp) == 0 && !ft_strchr(d->nw_tmp, '_'))
			|| d->nw_tmp[0] == '\0')
			ft_printf("bash: unset: `%s': not a valid identifier\n", d->nw_tmp);
		else
		{
			tmp = look_up(d->nw_head, d->echo);
			if (tmp)
			{
				delete_lst(d->nw_tmp, d->echo);
				set_alpha_index(d->echo, tmp->index, tmp->alpha);
				d->index--;
			}
		}
		a++;
	}
	return (0);
}
