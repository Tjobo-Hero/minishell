/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 10:47:29 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/20 11:09:06 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(int fd)
{
	if (fd > 1)
		close(fd);
}

static void	close_pipes(t_mini *d, int n)
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

static void	set_fd(t_mini *d, int c, int n, int x)
{
	ft_bzero(&d->pipe, sizeof(t_pipe));
	if (d->pipes && d->pipes[x] && d->pipes[x][1] > 1)
	{
		d->pipe.fd_out = d->pipes[x][1];
		d->pipe.ispipe[1] = 1;
	}
	if (d->pipes && x > 0 && d->pipes[x - 1] && d->pipes[x - 1][0] > 1)
	{
		d->pipe.fd_in = d->pipes[x - 1][0];
		d->pipe.ispipe[0] = 1;
	}
	d->args = redirect(d, x, c, n);
	command(d);
	close_fd(d->pipe.fd_in);
	close_fd(d->pipe.fd_out);
	ft_free(d->args);
	close_pipes(d, x);
}

static void	pipes_init(t_mini *d, int count)
{
	int	i;

	i = 0;
	d->pids = 0;
	d->pipes = ft_calloc(count, sizeof(int *));
	d->pipes == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	while (i + 1 < count)
	{
		d->pipes[i] = ft_calloc(3, sizeof(int));
		d->pipes[i] == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
		if (pipe(d->pipes[i]) == -1)
			error_malloc(d, NULL, NULL, NULL);
		i++;
	}
}

void		pipes(t_mini *d)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (d->arg->count[i] != 0)
		i++;
	if (i != 0)
		pipes_init(d, i);
	i = 0;
	while (d->arg->count[i] != 0)
	{
		set_fd(d, x, d->arg->count[i], i);
		x = d->arg->count[i];
		i++;
	}
	return_values(d);
	ft_free(d->orig);
	free(d->arg->count);
	free(d->arg);
}
