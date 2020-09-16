/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 14:50:52 by peer          #+#    #+#                 */
/*   Updated: 2020/09/16 14:58:21 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_output(char **args, t_pipe *redirs, int *i)
{
	redirs->output = args[*i + 1];
	if (redirs->fd_out > 1)
		close(redirs->fd_out);
	if (ft_strncmp(args[*i], ">", 2) == 0)
		redirs->fd_out = open(redirs->output, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else
		redirs->fd_out = open(redirs->output, O_CREAT | O_APPEND | O_RDWR, 0644);
}

void	redirect(t_mini *d)
{
	int		i;

	i = 0;
	while (d->args[i])
	{
		if (ft_strncmp(d->args[i], "<", 2) == 0 && d->args[i + 1])
		{
			d->pipe.input = d->args[i + 1];
			if (d->pipe.fd_in > 0)
				close(d->pipe.fd_in);
			d->pipe.fd_in = open(d->pipe.input, O_RDONLY);
		}
		if ((ft_strncmp(d->args[i], ">", 2) == 0 ||
			ft_strncmp(d->args[i], ">>", 3) == 0) && d->args[i + 1])
			redirect_output(d->args, &d->pipe, &i);
		i++;
	}
}
