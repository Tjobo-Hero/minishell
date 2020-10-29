/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export_utils1.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:09:28 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:09:31 by rbraaksm      ########   odam.nl         */
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

int		check_first_part(char *arg, int set)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	while (arg[i] != '\0')
	{
		if ((arg[i] > 64 && arg[i] < 91) || (arg[i] > 94 && arg[i] < 123))
		{
			check = 1;
			i++;
		}
		else if (arg[i] >= '0' && arg[i] <= '9')
		{
			if (check == 0)
				return (0);
			i++;
		}
		else
			return (0);
		if (arg[i] == '=' && set == 1)
			break ;
	}
	return (1);
}

int		check_arg(t_mini *d, t_new *new, char *arg)
{
	int		i;

	i = 0;
	d->new.set = 0;
	new->alpha = ' ';
	make_string(d, arg, new->tmp);
	while (new->tmp[i] != '=' && new->tmp[i] != '\0')
		i++;
	if (new->tmp[i] == '=')
		new->set = 1;
	ft_strlcpy(new->head, new->tmp, i + 1);
	if (new->set == 1)
	{
		ft_strlcpy(new->list, &new->tmp[i + 1], ft_strlen(&new->tmp[i]));
		ft_strlcpy(new->echo, &new->tmp[i + 1], ft_strlen(&new->tmp[i]));
		remove_quotes_and_slash(d, NULL, new->echo);
	}
	remove_quotes_and_slash(d, NULL, new->tmp);
	if (check_first_part(new->tmp, new->set) == 0)
		return (0);
	return (1);
}
