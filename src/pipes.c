/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 10:47:29 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/16 16:35:57 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int fd)
{
	if (fd > 1)
		close(fd);
}

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

void	do_pipes2(t_mini *d, int c, int *count)
{
	int		i;
	int		start;

	i = 0;
	start = (c == 0) ? 0 : count[c - 1] + 1;
	if (start == 0)
		d->args = malloc(sizeof(char*) * ((count[c] - 1) + 1));
	else
		d->args = malloc(sizeof(char*) * ((count[c] - start) + 1));
	while (start < count[c])
	{
		d->args[i] = ft_strdup(d->tmp_args[start]);
		start++;
		i++;
	}
	d->args[i] = NULL;
	// ft_bzero(&d->pipe, sizeof(t_pipe));
	// if (d->pipes && d->pipes[c] && d->pipes[c][1] > 1)
	// {
	// 	d->pipe.fd_out = d->pipes[c][1];
	// 	d->pipe.ispipe[1] = 1;
	// }
	// if (d->pipes && c > 0 && d->pipes[c - 1] && d->pipes[c - 1][0] > 1)
	// {
	// 	d->pipe.fd_in = d->pipes[c - 1][0];
	// 	d->pipe.ispipe[0] = 1;
	// }
	// redirect(d);
	run_commands(d);
	// ft_free(d->args);
	// close_pipes(d, c);
	return ;
}

void	pipes(t_mini *d, int c, int *count)
{
	do_pipes2(d, c, count);
	if (count[c + 1] != 0)
		pipes(d, c + 1, count);
}
