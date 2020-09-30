/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_init.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 17:23:46 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/30 18:34:05 by rbraaksm      ########   odam.nl         */
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

	i = 0;
	x = 0;
	start = 0;
	d->split_line = (char**)malloc(sizeof(char*) * (total_tmp(out, count) + 1));
	while (count[i] != 0)
	{
		len = count[i] - start;
		if (out[start] != '|')
		{
			d->split_line[x] = malloc(sizeof(char*) * len + 1);
			ft_strlcpy(d->split_line[x], &out[start], len + 1);
			x++;
		}
		start = count[i] + 1;
		i++;
	}
	d->split_line[x] = NULL;
}

static int	split_command(t_mini *d, char *line, int *count)
{
	char	*out;

	d->arg->c_i = 0;
	d->arg->c = -1;
	d->arg->i = 0;
	d->arg->set = 0;
	d->arg->a = 0;
	out = create_str(PATH_MAX);
	count = count_init(PATH_MAX);
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

	i = 0;
	count = count_init(PATH_MAX);
	c_cmd = new_count_commands(line, count, ';');
	cmd = new_fill_commands(line, count, c_cmd);
	while (i < PATH_MAX && i < c_cmd)
	{
		if (check_for_quotes(cmd[i]))
			printf("NOT CORRECT QUOTES\n");
		else
			split_command(d, cmd[i], count);
		pipes(d);
		ft_free(d->split_line);
		// free(count);
		// free(d->arg->count);
		i++;
	}
	ft_free(cmd);
	free(line);
}