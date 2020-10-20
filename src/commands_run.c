/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_run.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:01:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/19 21:50:45 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int fd)
{
	if (fd > 1)
		close(fd);
}

int		**(*start_command(int i))(t_mini *d)
{
	int	**(*command[7])(t_mini *d);

	command[0] = &pwd;
	command[1] = &cd;
	command[2] = &export;
	command[3] = &unset;
	command[4] = &exit_own;
	command[5] = &env;
	command[6] = &echo;
	return (command[i]);
}

t_cmd	*look_up_commands(char *name, t_cmd **hash_table)
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
	check_arg_and_remove_case(d);
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
	close_fd(d->pipe.fd_in);
	close_fd(d->pipe.fd_out);
}
