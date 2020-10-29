/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_table_set.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:14:29 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:14:31 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*set_elem(char *environ, int i, int len, int type)
{
	char	*tmp;

	if (type == 1)
	{
		tmp = malloc(sizeof(char) * i);
		if (tmp == NULL)
			return (NULL);
		ft_strlcpy(tmp, environ, i);
	}
	else
	{
		tmp = malloc(sizeof(char) * (len - i) + 1);
		if (tmp == NULL)
			return (NULL);
		ft_strlcpy(tmp, &environ[i], (len - i) + 1);
	}
	return (tmp);
}

t_env		*new_elem(t_mini *d, char *environ)
{
	t_env	*new;
	int		i;
	int		len;

	new = malloc(sizeof(t_env));
	new == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	i = 0;
	new->set = 0;
	len = ft_strlen(environ);
	while (environ[i] != '=' && environ[i] != '\0')
		i++;
	if (environ[i] == '=')
		new->set = 1;
	new->index = d->index;
	new->alpha = ' ';
	new->head = set_elem(environ, i + 1, len, 1);
	new->list = set_elem(environ, i + 1, len, 2);
	new->echo = set_elem(environ, i + 1, len, 2);
	new->head == NULL || new->list == NULL || new->echo == NULL ?
	error_malloc(d, NULL, NULL, NULL) : 0;
	new->next = NULL;
	return (new);
}

void		push_back(t_env **echo, t_env *new)
{
	t_env	*tmp;

	tmp = *echo;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*echo = new;
}
