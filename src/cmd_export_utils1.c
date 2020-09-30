/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export_utils1.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 09:53:24 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/30 18:18:29 by rbraaksm      ########   odam.nl         */
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

int		check_first_part(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (arg[i] > 64 && arg[i] < 91)
			i++;
		else if (arg[i] > 94 && arg[i] < 123)
			i++;
		else
			return (0);
	}
	return (1);
}

int		check_arg(t_mini *d, t_new *new, char *arg)
{
	int		i;
	char	*tmp;

	i = 0;
	d->new.set = ' ';
	tmp = create_str(PATH_MAX);
	make_string(d, arg, new->tmp);
	while (new->tmp[i] != '=' && new->tmp[i] != '\0')
		i++;
	ft_strlcpy(tmp, new->tmp, ft_strlen(new->tmp) + 1);
	if (check_first_part(tmp) == 0)
		return (0);
	if (tmp[i] == '=')
		new->set = '=';
	ft_strlcpy(new->list, &tmp[i + 1], ft_strlen(tmp));
	ft_strlcpy(new->head, tmp, i + 1);
	make_echo(d, new->echo, arg);
	free(tmp);
	return (1);
}
