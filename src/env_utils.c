/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 14:24:04 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/11 13:48:23 by rbraaksm      ########   odam.nl         */
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
				printf("%s - ", tmp->head);
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

void	swap(t_env **tmp, int i, int n)
{
	int tmp1;

	tmp1 = tmp[i]->index;
	tmp[i]->index = tmp[n]->index;
	tmp[n]->index = tmp1;
}

int		**alpha(t_env **env)
{
	int i;
	int c;
	int n;
	int d;

	d = 0;
	while (env[d] != NULL)
	{
		i = d;
		n = i + 1;
		while (env[n] != NULL)
		{
			c = ft_strncmp(env[i]->head, env[n]->head, ft_strlen(env[i]->head));
			if ((c > 0 && env[i]->index < env[n]->index) ||
				(c < 0 && env[i]->index > env[n]->index))
			{
				swap(env, i, n);
				i = d;
				n = i + 1;
			}
			else
				n++;
		}
		d++;
	}
	return (0);
}
