/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_table_alpha.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:14:24 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:14:26 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*find_next(t_env **env, t_env *tmp, int *i)
{
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->alpha == ' ')
			return (tmp);
		tmp = tmp->next;
	}
	(*i)++;
	if (env[*i] == NULL)
		(*i)++;
	while (*i < ECHO)
	{
		tmp = env[*i];
		while (tmp)
		{
			if (tmp->alpha == ' ')
				return (tmp);
			tmp = tmp->next;
		}
		(*i)++;
	}
	return (NULL);
}

static t_env	*find_free(t_env **env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (i < ECHO)
	{
		tmp = env[i];
		while (tmp)
		{
			if (tmp->alpha == ' ')
				return (tmp);
			tmp = tmp->next;
		}
		i++;
	}
	return (tmp);
}

static void		alpha_loop(t_env **env, t_env **next, t_env **cur, int *l)
{
	int		i;

	i = *l;
	while (*next != NULL)
	{
		if (ft_strncmp((*cur)->head, (*next)->head,
			ft_strlen((*cur)->head)) <= 0)
			*next = find_next(env, *next, &i);
		else
		{
			*cur = *next;
			*next = find_next(env, *next, &i);
		}
	}
}

void			alpha(t_env **env)
{
	t_env	*cur;
	t_env	*nex;
	int		i;
	int		l;
	int		sl;

	i = 0;
	l = 0;
	while (env[l] == NULL)
		l++;
	sl = l;
	cur = env[l];
	while (cur != NULL)
	{
		nex = cur;
		alpha_loop(env, &nex, &cur, &l);
		if (cur->alpha == ' ')
			cur->alpha = i;
		i++;
		l = sl;
		cur = find_free(env);
	}
}
