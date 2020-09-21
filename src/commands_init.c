/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_init.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 17:23:46 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/21 18:00:42 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**upgrade_args(t_arg *arg, char *out, int *count)
{
	char	**tmp;
	int		i;
	int		start;
	int		len;

	i = 0;
	tmp = (char**)malloc(sizeof(char*) * (arg->c_i + 2));
	start = 0;
	while (count[i] != 0)
	{
		len = count[i] - start;
		tmp[i] = malloc(sizeof(char*) * len + 1);
		ft_strlcpy(tmp[i], &out[start], len + 1);
		start = count[i] + 1;
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

static int	split_command(t_mini *d, char *line)
{
	int		i;
	char	out[PATH_MAX];
	int		count[PATH_MAX];

	i = 0;
	d->arg->c_i = 0;
	d->arg->c = -1;
	d->arg->i = 0;
	d->arg->set = 0;
	d->arg->p_i = 0;
	count_init(count);
	count_init(d->arg->count);
	ft_bzero(out, PATH_MAX);
	upgrade_line(d->arg, line, out, count);
	d->tmp_args = upgrade_args(d->arg, out, count);
	i = 0;
	while (d->tmp_args[i])
	{
		if (!check_for_quotes(d->tmp_args[i]))
			return (0);
		i++;
	}
	return (1);
}

void		get_commands(t_mini *d, char *line)
{
	char	**cmd;
	int		c_cmd;
	int		i;
	int		count[PATH_MAX];

	i = 0;
	c_cmd = new_count_commands(line, count, ';');
	cmd = new_fill_commands(line, count, c_cmd);
	while (i < PATH_MAX && i < c_cmd)
	{
		if (split_command(d, cmd[i]))
			find_pipes(d);
		else
			printf("NOT CORRECT QUOTES\n");
		ft_free(d->tmp_args);
		i++;
	}
	ft_free(cmd);
	free(line);
}