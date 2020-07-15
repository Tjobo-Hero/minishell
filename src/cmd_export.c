/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 14:19:31 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/07/15 14:58:12 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		**print(t_env **echo)
{
	t_env *tmp;
	int i;
	int c;

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
			if (tmp->set)
				write(1, "=\"", 2);
			ft_printf("%s", tmp->echo);
			if (tmp->set)
				write(1, "\"", 1);
			write(1, "\n", 1);
			i = 0;
			c++;
		}
		else
			i++;
	}
	return (0);
}

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
	int 	i;

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

void		new_list(t_mini *d, char *arg)
{
	int		i;

	i = 0;
	if (arg[0] < 65 || (arg[0] > 90 && arg[0] < 95) ||
		(arg[0] > 95 && arg[0] < 97) || arg[0] > 122)
		return ;
	set_env(&d->list[d->index], arg, d->index);
	d->list[d->index].alpha = find_lowest(d->echo, &d->list[d->index], d->index);
	set_alpha(d->echo, d->list[d->index].alpha);
	hash_table_insert_index(&d->list[d->index], d->echo, hash_echo(d->list[d->index].head));
	d->count++;
	d->index++;
}

int			replace(t_mini *d, t_env *env, int a, int len)
{
	char	*tmp;
	int		i;

	if (d->args[a][len] == '\0')
		return (0);
	i = ft_strlen(d->args[a]);
	env->set = 0;
	if (d->args[a][len] == '=')
		env->set = 1;
	tmp = env->head;
	clear_str(env->list);
	clear_str(env->echo);
	ft_strlcpy(env->list, d->args[a], i + 1);
	ft_strlcpy(env->echo, &d->args[a][len + 1], (i - len));
	return (0);
}

int		check_cmp(t_mini *d, int a)
{
	t_env	*tmp;
	char	*str;
	int		i;
	int		len;

	len = 0;
	i = 0;
	str = NULL;
	while (d->args[a][len] != '=' && d->args[a][len] != '\0')
		len++;
	if (d->args[a][len] == '=')
	{
		str = malloc(sizeof(char *) * len);
		/* malloc protection */
		ft_strlcpy(str, d->args[a], len + 1);
	}
	else
		str = ft_strdup(d->args[a]);
	tmp = look_up(str, d->echo);
	if (tmp == NULL)
		return (1);
	free(str);
	// return (replace(d, d->env[i], a, len));
	return (0);
}

int		**export(t_mini *d)
{
	int	a;

	a = 1;
	if (!d->args[1])
		return (print(d->echo));
	while (d->args[a])
	{
		if (check_cmp(d, a) == 1)
			new_list(d, d->args[a]);
		a++;
	}
	return (NULL);
}
