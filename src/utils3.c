/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 11:29:46 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 11:29:50 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	make_str(t_mini *d, t_env *tmp, int *i, int *c)
{
	char	*tmp1;

	tmp1 = ft_strjoin(tmp->head, "=");
	tmp1 == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	d->environ[*c] = ft_strjoin(tmp1, tmp->list);
	free(tmp1);
	d->environ[*c] == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	(*i) = 0;
	(*c)++;
}

void		make_environ(t_mini *d)
{
	t_env	*tmp;
	int		i;
	int		c;

	i = 0;
	c = 0;
	d->environ = ft_calloc((d->index + 1), (sizeof(char *)));
	d->environ == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	while (i < ECHO)
	{
		if (d->echo[i])
		{
			tmp = d->echo[i];
			while (tmp && tmp->index != c)
				tmp = tmp->next;
		}
		if (tmp != NULL && tmp->index == c)
			make_str(d, tmp, &i, &c);
		else
			i++;
	}
	d->environ[c] = NULL;
}

char		*new_orig(char *str, char *tmp, char *find, int i)
{
	char *tmp1;

	tmp1 = ft_strdup(str);
	if (tmp1 == NULL)
		return (NULL);
	free(str);
	if (tmp1[i] != '\0' && find == NULL)
		str = ft_strjoin(tmp, &tmp1[i]);
	else
		str = ft_strdup(tmp);
	if (str == NULL)
	{
		free(tmp1);
		return (NULL);
	}
	free(tmp1);
	return (str);
}
