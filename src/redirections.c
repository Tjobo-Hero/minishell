/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 14:50:52 by peer          #+#    #+#                 */
/*   Updated: 2020/10/21 21:42:46 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_array(t_mini *d, char **new, int start, int end)
{
	int		i;
	int		x;
	int		len;

	i = start;
	x = 0;
	while (d->orig[start] && start < end)
	{
		if (!ft_strncmp(d->orig[start], "<", 2) ||
			!ft_strncmp(d->orig[start], ">", 2)
			|| !ft_strncmp(d->orig[start], ">>", 3))
			start += 2;
		else
		{
			len = ft_strlen(d->orig[start]);
			new[x] = malloc(sizeof(char*) * (len + 1));
			new[x] == NULL ? error_malloc(d, new, NULL, NULL) : 0;
			ft_bzero(new[x], len + 1);
			ft_strlcpy(new[x], d->orig[start], len + 1);
			x++;
			start++;
		}
	}
	new[x] = NULL;
}

static char	**new_arg(t_mini *d, int start, int end)
{
	char	**new;
	int		i;
	int		startc;

	i = 0;
	startc = start;
	while (d->orig[start] && start < end)
	{
		if (!ft_strncmp(d->orig[start], "<", 2) ||
			!ft_strncmp(d->orig[start], ">", 2)
			|| !ft_strncmp(d->orig[start], ">>", 3))
			i++;
		start++;
	}
	new = malloc(sizeof(char **) * ((end - (i * 2)) + 1));
	new == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	d->cmd_echo = malloc(sizeof(char **) * ((end - (i * 2)) + 1));
	d->cmd_echo == NULL ? error_malloc(d, new, NULL, NULL) : 0;
	create_array(d, new, startc, end);
	create_array(d, d->cmd_echo, startc, end);
	return (new);
}

static void	redirect_output(t_mini *d, t_pipe *pipe, int i)
{
	int	check;

	check = 0;
	remove_case(d, d->orig[i + 1]);
	pipe->output = d->orig[i + 1];
	if (pipe->fd_out > 1)
		check = close(pipe->fd_out);
	if (ft_strncmp(d->orig[i], ">", 2) == 0)
		pipe->fd_out = open(pipe->output, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else
		pipe->fd_out = open(pipe->output,
		O_CREAT | O_APPEND | O_RDWR, 0644);
	if (pipe->fd_out == -1 || check == -1)
		error_malloc(d, NULL, NULL, NULL);
}

char		**redirect(t_mini *d, int x, int c, int n)
{
	int		i;
	int		s;

	s = d->arg->count[x];
	i = 0;
	while (d->orig[i] && i < s)
	{
		if (ft_strncmp(d->orig[i], "<", 2) == 0 && d->orig[i + 1])
		{
			d->pipe.input = d->orig[i + 1];
			if (d->pipe.fd_in > 0)
				close(d->pipe.fd_in);
			d->pipe.fd_in = open(d->pipe.input, O_RDONLY);
		}
		if ((ft_strncmp(d->orig[i], ">", 2) == 0 ||
			ft_strncmp(d->orig[i], ">>", 3) == 0) && d->orig[i + 1])
			redirect_output(d, &d->pipe, i);
		i++;
	}
	return (new_arg(d, c, n));
}
