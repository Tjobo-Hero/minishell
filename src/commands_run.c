/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_run.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:01:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/27 14:36:55 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**(*start_command(int i))(t_mini *d)
{
	int	**(*command[7])(t_mini *d);

	command[0] = &cmd_pwd;
	command[1] = &cmd_cd;
	command[2] = &cmd_export;
	command[3] = &cmd_unset;
	command[4] = &cmd_exit;
	command[5] = &cmd_env;
	command[6] = &cmd_echo;
	return (command[i]);
}

static t_cmd	*look_up_commands(char *name, t_cmd **hash_table)
{
	t_cmd	*tmp;
	int		i;
	int		len;

	i = hash(name, COMMAND);
	len = ft_strlen(name);
	tmp = hash_table[i];
	while (tmp)
	{
		if (!strncmp(name, tmp->command, strlen(tmp->command)) &&
			len == (int)ft_strlen(tmp->command))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

static int	**run_commands(t_mini *d, int forked)
{
	t_cmd	*tmp;

	d->fd = (d->pipe.fd_out > 0) ? d->pipe.fd_out : 1;
	d->forked = forked;
	tmp = look_up_commands(d->args[0], d->commands);
	if (tmp == NULL)
		check_if_forked(d);
	else
		d->ret = (int)start_command(tmp->index)(d);
	return (0);
}

void		command(t_mini *d)
{
	if (d->pipe.ispipe[0] == 1 || d->pipe.ispipe[1] == 1)
	{
		if (fork() == 0)
		{
			run_commands(d, 1);
			exit(0);
		}
		else
			d->pids++;
	}
	else
		run_commands(d, 0);
}
