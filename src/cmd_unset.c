/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_unset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:15:38 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:15:40 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_alpha_index(t_mini *d, char *del, int index, int alpha)
{
	t_env	*tmp;
	int		i;

	i = 0;
	delete_lst(del, d->echo);
	while (i < ECHO)
	{
		if (d->echo[i])
		{
			tmp = d->echo[i];
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
	d->index--;
}

int			**cmd_unset(t_mini *d)
{
	t_env	*tmp;
	int		a;

	a = 1;
	create_delete_new(d, &d->new, 0);
	while (d->orig[a])
	{
		if ((check_arg(d, &d->new, d->orig[a]) == 0 &&
		ft_isalpha_str(d->new.tmp) == 0 && !ft_strchr(d->new.tmp, '_'))
		|| d->new.tmp[0] == '\0')
			print_error("bash: unset: `", d->new.tmp,
			"': not a valid identifier", NULL);
		else
		{
			tmp = look_up(d->new.head, d->echo);
			if (tmp)
				set_alpha_index(d, d->new.tmp, tmp->index, tmp->alpha);
		}
		create_delete_new(d, &d->new, 1);
		a++;
	}
	create_delete_new(d, &d->new, 3);
	return (0);
}
