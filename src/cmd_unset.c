/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_unset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 14:55:19 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/20 11:12:28 by rbraaksm      ########   odam.nl         */
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

int		**cmd_unset(t_mini *d)
{
	t_env	*tmp;
	int		a;

	a = 1;
	create_delete_new(d, &d->new, 0);
	while (d->orig[a])
	{
		check_arg(d, &d->new, d->orig[a]);
		if ((ft_isalpha_str(d->new.tmp) == 0 && !ft_strchr(d->new.tmp, '_'))
			|| d->new.tmp[0] == '\0')
			ft_printf("bash: unset: `%s': not a valid identifier\n", d->new.tmp);
		else
		{
			tmp = look_up(d->new.head, d->echo);
			if (tmp)
			{
				delete_lst(d->new.tmp, d->echo);
				set_alpha_index(d->echo, tmp->index, tmp->alpha);
				d->index--;
			}
		}
		create_delete_new(d, &d->new, 1);
		a++;
	}
	create_delete_new(d, &d->new, 2);
	return (0);
}
