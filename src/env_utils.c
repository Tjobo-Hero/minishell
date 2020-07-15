/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 14:24:04 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/15 11:08:57 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_env **hash_table)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (i < ECHO)
	{
		if (hash_table[i] == NULL)
			printf("\t%i\t---\n", i);
		else
		{
			printf("\t%i\t", i);
			tmp = hash_table[i];
			while (tmp != NULL)
			{
				printf("[%d] %s - ", tmp->alpha, tmp->head);
				tmp = tmp->next;
			}
			printf("\n");
		}
		i++;
	}
}

void	print_env(t_env **hash_table)
{
	int		i;

	i = 0;
	while (i < ENV_SIZE)
	{
		if (hash_table[i] == NULL)
			printf("\t%i\t---\n", i);
		else
			printf("\t%i\t%s\n", i, hash_table[i]->head);
		i++;
	}
}

unsigned int	hash_env(char *name)
{
	int				length;
	unsigned int	value;
	int				i;

	value = 0;
	i = 0;
	length = strlen(name);
	while (i < length)
	{
		value += name[i];
		value = (value * name[i]) % ENV_SIZE;
		i++;
	}
	return (value);
}

unsigned int	hash_echo(char *name)
{
	int				length;
	unsigned int	value;
	int				i;

	value = 0;
	i = 0;
	length = strlen(name);
	while (i < length)
	{
		value += name[i];
		value = (value * name[i]) % ECHO;
		i++;
	}
	return (value);
}

t_env	*look_up(char *name, t_env **hash_table)
{
	t_env	*tmp;
	int		i;

	i = hash_echo(name);
	tmp = hash_table[i];
	while (tmp != NULL && strncmp(tmp->head, name, strlen(name)) != 0)
		tmp = tmp->next;
	return (tmp);
}

void	delete_lst(char *name, t_env **hash_table)
{
	t_env	*tmp;
	t_env	*pre;
	int		i;

	i = hash_echo(name);
	tmp = hash_table[i];
	pre = NULL;
	while (tmp != NULL && strncmp(tmp->head, name, strlen(name)) != 0)
	{
		pre = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	if (pre == NULL)
		hash_table[i] = tmp->next;
	else
		pre->next = tmp->next;
}

void	hash_table_insert(t_env *name, t_env **hash_table)
{
	int	index;

	if (name == NULL)
		return ;
	index = hash_echo(name->head);
	name->next = hash_table[index];
	hash_table[index] = name;
	return ;
}

void	print_new(t_env **hash_table)
{
	t_env	*tmp;
	int		c;
	int		i;

	c = 0;
	i = 0;
	while (i < ECHO)
	{
		if (hash_table[i] != NULL)
		{
			tmp = hash_table[i];
			while (tmp && tmp->alpha != c)
				tmp = tmp->next;
		}
		if (tmp != NULL && tmp->alpha == c)
		{
			printf("[%2d] %s\n", tmp->alpha, tmp->head);
			c++;
			i = 0;
		}
		else
			i++;
	}
}

t_env	*find_next(t_env **env, t_env *tmp, int *i)
{
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->alpha == ' ')
			return (tmp);
		tmp = tmp->next;
	}
	*i = *i + 1;
	while (env[*i] == NULL)
		*i = *i + 1;
	while (*i < ECHO)
	{
		tmp = env[*i];
		while (tmp)
		{
			if (tmp->alpha == ' ')
				return (tmp);
			tmp = tmp->next;
		}
		*i = *i + 1;
	}
	return (NULL);
}

t_env	*find_free(t_env **env)
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

int		**alpha(t_env **env)
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
		nex = find_free(env);
		while (nex != NULL)
		{
			if (ft_strncmp(cur->head, nex->head, ft_strlen(cur->head)) <= 0)
				nex = find_next(env, nex, &l);
			else
			{
				cur = nex;
				nex = find_next(env, nex, &l);
			}
		}
		if (cur->alpha == ' ')
			cur->alpha = i;
		i++;
		l = sl;
		cur = find_free(env);
	}
	return (0);
}
