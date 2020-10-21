/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 14:50:52 by peer          #+#    #+#                 */
/*   Updated: 2020/10/21 10:06:43 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_new(t_mini *d, char **new)
{
	int		i;

	i = 0;
	ft_free(d->orig);
	while (new[i])
		i++;
	d->orig = (char**)malloc(sizeof(char*) * (i + 1));
	d->orig == NULL ? error_malloc(d, new, NULL, NULL) : 0;
	i = 0;
	while (new[i])
	{
		d->orig[i] = ft_strdup(new[i]);
		d->orig[i] == NULL ? error_malloc(d, new, NULL, NULL) : 0;
		i++;
	}
	d->orig[i] = NULL;
}

static void	create_new(t_mini *d, char **new)
{
	int		i;
	int		x;
	int		len;

	i = 0;
	x = 0;
	while (d->orig[i])
	{
		if (!ft_strncmp(d->orig[i], "<", 2) || !ft_strncmp(d->orig[i], ">", 2)
			|| !ft_strncmp(d->orig[i], ">>", 3))
			i += 2;
		else
		{
			len = ft_strlen(d->orig[i]);
			new[x] = malloc(sizeof(char*) * (len + 1));
			new[x] == NULL ? error_malloc(d, new, NULL, NULL) : 0;
			ft_bzero(new[x], len + 1);
			ft_strlcpy(new[x], d->orig[i], len + 1);
			x++;
			i++;
		}
	}
	new[x] = NULL;
}

static char	**new_arg(t_mini *d, int c, int n)
{
	char	**new;
	int		i;
	int		x;

	i = 0;
	while (d->orig[c] && c < n)
	{
		if (!ft_strncmp(d->orig[c], "<", 2) || !ft_strncmp(d->orig[c], ">", 2)
			|| !ft_strncmp(d->orig[c], ">>", 3))
			i++;
		c++;
	}
	new = malloc(sizeof(char **) * ((n - (i * 2)) + 1));
	new == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	i = 0;
	x = 0;
	create_new(d, new);
	copy_new(d, new);
	return (new);
}

static void	redirect_output(t_mini *d, char **args, t_pipe *redirs, int *i)
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

char		**redirect(t_mini *d, int x, int c, int n)
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
