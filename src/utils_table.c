/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_table.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:14:34 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 13:05:08 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		hash(char *name, int count)
{
	int				length;
	unsigned int	value;
	int				i;

	value = 0;
	i = 0;
	length = ft_strlen(name);
	while (i < length)
	{
		value += name[i];
		value = (value * name[i]) % count;
		i++;
	}
	return (value);
}

t_env	*look_up(char *name, t_env **hash_table)
{
	t_env	*tmp;
	int		i;

	i = hash(name, ECHO);
	tmp = hash_table[i];
	while (tmp != NULL && ft_strncmp(tmp->head, name, strlen(name)) != 0)
		tmp = tmp->next;
	return (tmp);
}

void	delete_lst(char *name, t_env **hash_table)
{
	t_env	*tmp;
	t_env	*pre;
	int		i;

	i = hash(name, ECHO);
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
	free(tmp->head);
	free(tmp->list);
	free(tmp->echo);
	free(tmp);
}
