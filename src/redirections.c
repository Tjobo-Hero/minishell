/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 14:50:52 by peer          #+#    #+#                 */
/*   Updated: 2020/10/16 13:19:59 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_output(t_mini *d, char **args, t_pipe *redirs, int *i)
{
	int	check;

	redirs->output = args[*i + 1];
	if (redirs->fd_out > 1)
		check = close(redirs->fd_out);
	if (ft_strncmp(args[*i], ">", 2) == 0)
		redirs->fd_out = open(redirs->output, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else
		redirs->fd_out = open(redirs->output,
		O_CREAT | O_APPEND | O_RDWR, 0644);
	if (redirs->fd_out == -1 || check == -1)
		malloc_error_test(d, NULL, NULL, NULL);
}

void	redirect(t_mini *d, int n)
{
	int		i;
	int		x;

	x = d->arg->count[n];
	i = d->arg->count[n - 1];
	while (d->split_line[i] && i < x)
	{
		if (ft_strncmp(d->split_line[i], "<", 2) == 0 && d->split_line[i + 1])
		{
			d->pipe.input = d->split_line[i + 1];
			if (d->pipe.fd_in > 0)
				close(d->pipe.fd_in);
			d->pipe.fd_in = open(d->pipe.input, O_RDONLY);
		}
		if ((ft_strncmp(d->split_line[i], ">", 2) == 0 ||
			ft_strncmp(d->split_line[i], ">>", 3) == 0) && d->split_line[i + 1])
			redirect_output(d, d->split_line, &d->pipe, &i);
		i++;
	}
}
