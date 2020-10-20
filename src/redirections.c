/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 14:50:52 by peer          #+#    #+#                 */
/*   Updated: 2020/10/20 10:31:45 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_arg(t_mini *d, int c, int n)
{
	char	**new;
	int		len;
	int		i;
	int		x;

	x = 0;
	i = c;
	while (d->orig[c] && c < n && (ft_strncmp(d->orig[c], "<", 2) &&
		ft_strncmp(d->orig[c], ">", 2) && ft_strncmp(d->orig[c], ">>", 3)))
		c++;
	new = malloc(sizeof(char **) * ((c - i) + 1));
	new == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	while (i < c)
	{
		len = ft_strlen(d->orig[i]);
		new[x] = malloc(sizeof(char*) * (len + 1));
		new[x] == NULL ? error_malloc(d, new, NULL, NULL) : 0;
		ft_bzero(new[x], len + 1);
		ft_strlcpy(new[x], d->orig[i], len + 1);
		x++;
		i++;
	}
	new[x] = NULL;
	return (new);
}

void	redirect_output(t_mini *d, char **args, t_pipe *redirs, int *i)
{
	int	check;

	check = 0;
	redirs->output = args[*i + 1];
	if (redirs->fd_out > 1)
		check = close(redirs->fd_out);
	if (ft_strncmp(args[*i], ">", 2) == 0)
		redirs->fd_out = open(redirs->output, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else
		redirs->fd_out = open(redirs->output,
		O_CREAT | O_APPEND | O_RDWR, 0644);
	if (redirs->fd_out == -1 || check == -1)
		error_malloc(d, NULL, NULL, NULL);
}

char	**redirect(t_mini *d, int x, int c, int n)
{
	int		i;
	int		s;

	s = d->arg->count[x];
	i = d->arg->count[x - 1];
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
			redirect_output(d, d->orig, &d->pipe, &i);
		i++;
	}
	return (new_arg(d, c, n));
}
