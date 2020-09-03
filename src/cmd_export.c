/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 14:19:31 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/09/03 10:36:16 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		**print(t_env **echo)
{
	t_env	*tmp;
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (i < ECHO)
	{
		if (echo[i] != NULL)
		{
			tmp = echo[i];
			while (tmp)
			{
				if (tmp->alpha == c)
					break ;
				tmp = tmp->next;
			}
		}
		if (tmp != NULL && tmp->alpha == c)
		{
			ft_printf("declare -x %s", tmp->head);
			tmp->set ? write(1, "=\"", 2) : 0;
			ft_printf("%s", tmp->echo);
			tmp->set ? write(1, "\"", 1) : 0;
			write(1, "\n", 1);
			i = 0;
			c++;
		}
		else
			i++;
	}
	return (0);
}

int		replace(t_mini *d, t_env *tmp)
{
	tmp->set = 0;
	if (ft_strchr(d->nw_list, '=') != 0)
		tmp->set = 1;
	d->list[tmp->index].set = tmp->set;
	clear_str(d->list[tmp->index].list);
	clear_str(d->list[tmp->index].echo);
	ft_strlcpy(d->list[tmp->index].list, d->nw_list, ft_strlen(d->nw_list));
	ft_strlcpy(d->list[tmp->index].echo, d->nw_echo, ft_strlen(d->nw_echo) + 1);
	return (0);
}

int		check_cmp(t_mini *d)
{
	t_env	*tmp;

	tmp = look_up(d->nw_head, d->echo);
	if (tmp == NULL)
		return (1);
	return (replace(d, tmp));
}

int		**export(t_mini *d)
{
	int	a;

	a = 1;
	if (!d->args[1])
		return (print(d->echo));
	while (d->args[a])
	{
		clear_str(d->nw_list);
		clear_str(d->nw_head);
		clear_str(d->nw_echo);
		if (check_arg(d, d->args[a]) == 0)
			printf("bash: export: `%s': not a valid identifier\n", d->nw_list);
		else if (check_cmp(d) == 1)
			new_list(d);
		a++;
	}
	printf("\n");
	return (NULL);
}
