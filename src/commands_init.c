/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_init.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 17:23:46 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/15 18:25:43 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	total_tmp(char *out, int *count)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (count[i] != 0)
	{
		if (out[count[i] + 1] != '|')
			len++;
		i++;
	}
	return (len);
}

static void	split_line(t_mini *d, char *out, int *count)
{
	int		i;
	int		x;
	int		start;
	int		len;
	int		z;

	i = 0;
	x = 0;
	start = 0;
	z = total_tmp(out, count);
	d->split_line = (char**)malloc(sizeof(char*) * (z + 1));
	d->orig = (char**)malloc(sizeof(char*) * (z + 1));
	d->split_line == NULL || d->orig == NULL ? malloc_error() : 0;
	while (count[i] != 0)
	{
		len = count[i] - start;
		if (out[start] != '|')
		{
			d->split_line[x] = malloc(sizeof(char*) * len + 1);
			d->split_line[x] == NULL ? malloc_error() : 0;
			ft_strlcpy(d->split_line[x], &out[start], len + 1);
			d->orig[x] = ft_strdup(d->split_line[x]);
			d->orig[x] == NULL ? malloc_error() : 0;
			x++;
		}
		start = count[i] + 1;
		i++;
	}
	d->split_line[x] = NULL;
	d->orig[x] = NULL;
}

static int	split_command(t_mini *d, char *line, int *count)
{
	char	*out;

	d->arg = (t_arg*)malloc(sizeof(t_arg) * (1));
	d->arg == NULL ? malloc_error() : 0;
	d->arg->c_i = 0;
	d->arg->c = -1;
	d->arg->i = 0;
	d->arg->set = 0;
	d->arg->a = 0;
	out = ft_calloc(PATH_MAX, sizeof(char*));
	out == NULL ? malloc_error() : 0;
	ft_bzero(count, PATH_MAX + 1);
	d->arg->count = count_init(PATH_MAX);
	upgrade_line(d->arg, line, out, count);
	split_line(d, out, count);
	free(out);
	return (1);
}

void		get_commands(t_mini *d, char *line)
{
	char	**cmd;
	int		c_cmd;
	int		i;
	int		*count;
	int		x;

	i = 0;
	x = syntax_check(line);
	if (x == -1 || x == -2)
	{
		ft_putstr_fd("NOT CORRECT\n", d->fd);
		return ;
	}
	count = count_init(PATH_MAX);
	c_cmd = new_count_commands(line, count, ';');
	cmd = new_fill_commands(line, count, c_cmd);
	cmd == NULL ? malloc_error() : 0;
	while (cmd[i])
	{
		split_command(d, cmd[i], count);
		if (d->split_line[0])
		{
			pipes(d);
			ft_free(d->split_line);
			ft_free(d->orig);
		}
		free(count);
		free(d->arg->count);
		free(d->arg);
		i++;
	}
	ft_free(cmd);
}
