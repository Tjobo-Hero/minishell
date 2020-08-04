/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environ_init.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/08 17:02:56 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/08/04 23:01:13 by rbraaksm      ########   odam.nl         */
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

void			init(t_env **tmp)
{
	int	i;

	i = 0;
	while (i < ECHO)
	{
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
	init(d->echo);
	while (environ[d->index] != NULL)
	{
		set_env(&d->list[d->index], environ[d->index], d->index);
		hash_table_insert_index(&d->list[d->index], d->echo,
		hash_echo(d->list[d->index].head, ECHO));
		d->index++;
	}
	alpha(d->echo);
}

void			set_env1(t_cmd *user, char *command, int index)
{
	int		len;

	len = ft_strlen(command);
	user->index = index;
	ft_strlcpy(user->head, command, len + 1);
}

void			hash_table_insert_index2(t_mini *d , char *command, int index, int hash)
{
	if (command == NULL)
		return ;
	set_env1(&d->cmd_list[index], command, index);
	ft_strlcpy(d->cmd_list[index].head, command, ft_strlen(command) + 1);
	d->cmd_list[index].index = index;
	d->cmd_list[index].next = d->commands[hash];
	d->commands[hash] = &d->cmd_list[index];
}

void			init_commands(t_mini *d)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		d->commands[i] = NULL;
		i++;
	}
	i = 0;
	hash_table_insert_index2(d, "pwd", 0, hash_echo("pwd", 7));
	hash_table_insert_index2(d, "cd", 1, hash_echo("cd", 7));
	hash_table_insert_index2(d, "export", 2, hash_echo("export", 7));
	hash_table_insert_index2(d, "unset", 3, hash_echo("unset", 7));
	hash_table_insert_index2(d, "exit", 4, hash_echo("exit", 7));
	hash_table_insert_index2(d, "env", 5, hash_echo("env", 7));
	hash_table_insert_index2(d, "echo", 6, hash_echo("echo", 7));
}