/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 14:19:31 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/09/03 13:49:06 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_export2(t_env *tmp, int *i)
{
	ft_printf("declare -x %s", tmp->head);
	tmp->set ? write(1, "=\"", 2) : 0;
	ft_printf("%s", tmp->echo);
	tmp->set ? write(1, "\"", 1) : 0;
	write(1, "\n", 1);
	*i = 0;
	return (1);
}

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
			c += print_export2(tmp, &i);
		else
			i++;
	}
	return (0);
}

int		replace(t_mini *d, t_env *tmp)
{
	tmp->set = 0;
	if (ft_strchr(d->nw_list, '=') != NULL)
		tmp->set = 1;
	d->list[tmp->index].set = tmp->set;
	clear_str(d->list[tmp->index].list);
	clear_str(d->list[tmp->index].echo);
	ft_strlcpy(d->list[tmp->index].list, d->nw_list, ft_strlen(d->nw_list) + 1);
	ft_strlcpy(d->list[tmp->index].echo, d->nw_echo, ft_strlen(d->nw_echo) + 1);
	return (0);
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

int		**export(t_mini *d)
{
	t_env	*tmp;
	int		a;

	a = 1;
	if (!d->args[1])
		return (print(d->echo));
	while (d->args[a])
	{
		clear_str(d->nw_list);
		clear_str(d->nw_head);
		clear_str(d->nw_echo);
		if (check_arg(d, d->args[a]) == 0 || d->nw_list[0] == '\0')
			printf("bash: export: `%s': not a valid identifier\n", d->nw_list);
		else
		{
			tmp = look_up(d->nw_head, d->echo);
			if (tmp != NULL && ft_strchr(d->nw_list, '=') != 0)
				replace(d, tmp);
			else if (tmp == NULL)
				new_list(d);
		}
		a++;
	}
	return (NULL);
}
