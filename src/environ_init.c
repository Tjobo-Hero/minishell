/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environ_init.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/08 17:02:56 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/04 15:34:00 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(t_env *user, char *environ, int index)
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
	ft_strlcpy(user->list, &environ[i + 1], (len - i) + 1);
	ft_strlcpy(user->echo, &environ[i + 1], (len - i + 1));
}

void	init(t_env **tmp, t_cmd **command, int x)
{
	int	i;

	i = 0;
	if (tmp != NULL)
	{
		while (i < x)
		{
			tmp[i] = NULL;
			i++;
		}
		return ;
	}
	while (i < x)
	{
		command[i] = NULL;
		i++;
	}
}

void	set_env_cmd(t_cmd *user, char *command, int index)
{
	int		len;

	len = ft_strlen(command);
	user->index = index;
	ft_strlcpy(user->head, command, len + 1);
}

void	hash_table_insert_index(t_mini *d, t_env *user, t_env **env, int hash)
{
	char	*cmd;

	user->next = env[hash];
	env[hash] = user;
	if (d->index == 0)
	{
		while (d->index < 7)
		{
			d->index == 0 ? cmd = "pwd" : 0;
			d->index == 1 ? cmd = "cd" : 0;
			d->index == 2 ? cmd = "export" : 0;
			d->index == 3 ? cmd = "unset" : 0;
			d->index == 4 ? cmd = "exit" : 0;
			d->index == 5 ? cmd = "env" : 0;
			d->index == 6 ? cmd = "echo" : 0;
			set_env_cmd(&d->cmd_list[d->index], cmd, d->index);
			ft_strlcpy(d->cmd_list[d->index].head, cmd, ft_strlen(cmd) + 1);
			d->cmd_list[d->index].index = d->index;
			d->cmd_list[d->index].next = d->commands[hash_echo(cmd, 7)];
			d->commands[hash_echo(cmd, 7)] = &d->cmd_list[d->index];
			d->index++;
		}
		d->index = 0;
	}
}

void	init_env(t_mini *d)
{
	extern char **environ;

	d->index = 0;
	init(d->echo, NULL, ECHO);
	init(NULL, d->commands, 8);
	while (environ[d->index] != NULL)
	{
		set_env(&d->list[d->index], environ[d->index], d->index);
		hash_table_insert_index(d, &d->list[d->index], d->echo,
		hash_echo(d->list[d->index].head, ECHO));
		d->index++;
	}
	alpha(d->echo);
}
