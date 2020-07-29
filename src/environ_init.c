/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environ_init.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/08 17:02:56 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/28 17:44:51 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			set_env(t_env *user, char *environ, int index)
{
	int		i;
	int		len;

	i = 0;
	user->set = 0;
	len = ft_strlen(environ);
	while (environ[i] != '=' && environ[i] != '\0')
		i++;
	if (environ[i] == '=')
		user->set = 1;
	user->index = index;
	user->alpha = ' ';
	ft_strlcpy(user->head, environ, i + 1);
	ft_strlcpy(user->list, environ, len + 1);
	ft_strlcpy(user->echo, &environ[i + 1], (len - i + 1));
}

void			init(t_env **tmp, int x)
{
	int	i;

	i = 0;
	while (i < x)
	{
		if (x == 50)
			tmp[i] = NULL;
		else
			tmp[i] = NULL;
		i++;
	}
}

void			hash_table_insert_index(t_env *user, t_env **env, int hash)
{
	if (user == NULL)
		return ;
	user->next = env[hash];
	env[hash] = user;
	return ;
}

void			init_env(t_mini *d)
{
	extern char **environ;

	d->index = 0;
	init(d->echo, ECHO);
	while (environ[d->index] != NULL)
	{
		set_env(&d->list[d->index], environ[d->index], d->index);
		hash_table_insert_index(&d->list[d->index], d->echo,
		hash_echo(d->list[d->index].head));
		// printf("[%d] %s\n", d->index, d->list[d->index].head);
		// printf("ENVIRON: %s\n\n", environ[d->index]);
		d->index++;
	}
	alpha(d->echo);
}
