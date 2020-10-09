/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/08 17:02:56 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/09 17:43:54 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	hash(char *name)
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

void			set_env(t_env *user, char *environ, int env_or_echo)
{
	int		i;
	int		len;

	i = 0;
	user->set = 0;
	len = ft_strlen(environ);
	while (environ[i] != '=' && environ[i] != '\0')
		i++;
	ft_strlcpy(user->head, environ, i + 1);
	if (env_or_echo == 0)
	{
		if (environ[i] == '=')
			user->set = 1;
		ft_strlcpy(user->list, environ, len + 1);
	}
	else
		ft_strlcpy(user->list, &environ[i + 1], (len - i));
}

void			init(t_mini *d, int x)
{
	int	i;

	i = 0;
	while (i < x)
	{
		if (x == 50)
			d->env[i] = NULL;
		else
			d->echo[i] = NULL;
		i++;
	}
}

void			hash_table_insert(t_env *user, t_env **env, int index)
{
	if (user == NULL)
		return ;
	user->next = env[index];
	env[index] = user;
	return ;
}

// void			init_env(t_env **env, t_env **echo)
// {
// 	t_env		env_e[ENV_SIZE];
// 	t_env		echo_e[ENV_SIZE];
// 	extern char **environ;
// 	int			i;

// 	init(env);
// 	init(echo);
// 	i = 0;
// 	while (environ[i] != NULL)
// 	{
// 		set_env(&env_e[i], environ[i], 0);
// 		set_env(&echo_e[i], environ[i], 1);
// 		// hash_table_insert(&env_e[i], env, i);
// 		// hash_table_insert(&echo_e[i], echo, hash(echo_e[i].head));
// 		i++;
// 	}
// }

void			init_env(t_mini *d)
{
	t_env		env_e[ENV_SIZE];
	t_env		echo_e[ENV_SIZE];
	extern char **environ;
	int			i;

	init(d, ENV_SIZE);
	init(d, ECHO);
	i = 0;
	(void)env_e;
	(void)echo_e;
	while (environ[i] != NULL)
	{
		set_env(&env_e[i], environ[i], 0);
		set_env(&echo_e[i], environ[i], 1);
		hash_table_insert(&env_e[i], d->env, i);
		hash_table_insert(&echo_e[i], d->echo, hash(echo_e[i].head));
		i++;
	}
}