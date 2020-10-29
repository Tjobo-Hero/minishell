/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:09:46 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:09:48 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_export2(t_mini *d, t_env *tmp, int *i)
{
	ft_putstr_fd("declare -x ", d->fd);
	ft_putstr_fd(tmp->head, d->fd);
	tmp->set ? write(d->fd, "=\"", 2) : 0;
	ft_putstr_fd(tmp->list, d->fd);
	tmp->set ? write(d->fd, "\"", 1) : 0;
	write(d->fd, "\n", 1);
	*i = 0;
	return (1);
}

static int	**print(t_mini *d)
{
	t_env	*tmp;
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (i < ECHO)
	{
		if (d->echo[i] != NULL)
		{
			tmp = d->echo[i];
			while (tmp)
			{
				if (tmp->alpha == c)
					break ;
				tmp = tmp->next;
			}
		}
		if (tmp != NULL && tmp->alpha == c)
			c += print_export2(d, tmp, &i);
		else
			i++;
	}
	return ((int**)0);
}

static int	replace(t_mini *d, t_env *tmp)
{
	tmp->set = d->new.set;
	free(tmp->list);
	free(tmp->echo);
	tmp->list = ft_strdup(d->new.list);
	tmp->echo = ft_strdup(d->new.echo);
	tmp->list == NULL || tmp->echo == NULL ?
	error_malloc(d, NULL, NULL, NULL) : 0;
	return (0);
}

static void	new_list(t_mini *d)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	new->set = 0;
	if (d->new.set)
		new->set = 1;
	new->index = d->index;
	new->head = set_elem(d->new.head, ft_strlen(d->new.head) + 1, 0, 1);
	new->list = set_elem(d->new.list, ft_strlen(d->new.list) + 1, 0, 1);
	new->echo = set_elem(d->new.echo, ft_strlen(d->new.echo) + 1, 0, 1);
	new->next = NULL;
	new->alpha = find_lowest(d->echo, new, new->index);
	set_alpha(d->echo, new->alpha);
	push_back(&d->echo[hash(new->head, ECHO)], new);
	d->index++;
}

int			**cmd_export(t_mini *d)
{
	t_env	*tmp;
	int		a;

	a = 1;
	if (!d->args[a])
		return (print(d));
	create_delete_new(d, &d->new, 0);
	while (d->orig[a])
	{
		if (check_arg(d, &d->new, d->orig[a]) == 0 || d->new.head[0] == '\0')
			print_error("bash: export: `", d->new.tmp,
			"': not a valid identifier", NULL);
		else
		{
			tmp = look_up(d->new.head, d->echo);
			if (tmp != NULL && d->new.set == 1)
				replace(d, tmp);
			else if (tmp == NULL)
				new_list(d);
		}
		create_delete_new(d, &d->new, 1);
		a++;
	}
	create_delete_new(d, &d->new, 3);
	return ((int**)0);
}
