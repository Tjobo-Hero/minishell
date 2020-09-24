/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 10:47:29 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/24 14:09:28 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	close_fd(int fd)
// {
// 	if (fd > 1)
// 		close(fd);
// }

void	close_pipes(t_mini *d, int n)
{
	if (d->pipes)
	{
		if (d->pipes[n] && d->pipes[n][1] > 1)
		{
			close(d->pipes[n][1]);
			d->pipes[n][1] = -1;
		}
		if (n > 0 && d->pipes[n - 1] && d->pipes[n - 1][0] > 1)
		{
			close(d->pipes[n - 1][0]);
			d->pipes[n - 1][0] = -1;
		}
	}
}


static void	pipes_start(t_mini *d, int c, int n)
{
	ft_bzero(&d->pipe, sizeof(t_pipe));
	if (d->pipes && d->pipes[c] && d->pipes[c][1] > 1)
	{
		d->pipe.fd_out = d->pipes[c][1];
		d->pipe.ispipe[1] = 1;
	}
	if (d->pipes && c > 0 && d->pipes[c - 1] && d->pipes[c - 1][0] > 1)
	{
		d->pipe.fd_in = d->pipes[c - 1][0];
		d->pipe.ispipe[0] = 1;
	}
	redirect(d, n);
	d->args = new_arg(d->split_line, c, n);
	command(d);
	ft_free(d->args);
	free_int_array(d->pipes);
	close_pipes(d, c);
	return ;
}

static void	pipes_init(t_mini *d, int count)
{
	int	i;

	i = 0;
	d->pids = 0;
	d->pipes = ft_calloc(count, sizeof(int *));
	if (d->pipes == NULL)
		exit(1);
	while (i + 1 < count)
	{
		d->pipes[i] = ft_calloc(3, sizeof(int));
		if (d->pipes[i] == NULL)
			exit(1);
		if (pipe(d->pipes[i]) == -1)
			exit(1);
		i++;
	}
}

void	pipes(t_mini *d)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (d->split_line[i])
		i++;
	if (i != 0)
		pipes_init(d, i + 1);
	i = 0;
	while (d->arg->count[i] != 0)
	{
		pipes_start(d, x, d->arg->count[i]);
		x = d->arg->count[i];
		i++;
	}
}
