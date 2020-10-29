/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:15:52 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 13:06:26 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	total_words(char *out, int *count)
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

static char	**split_line(t_mini *d, char *out, int *count)
{
	char	**tmp;
	int		i;
	int		x;
	int		start;
	int		len;

	i = 0;
	x = 0;
	start = 0;
	tmp = (char**)ft_calloc((total_words(out, count) + 1), sizeof(char*));
	tmp == NULL ? error_malloc(d, NULL, out, count) : 0;
	while (count[i] != 0)
	{
		len = count[i] - start;
		if (out[start] != '|')
		{
			tmp[x] = malloc(sizeof(char*) * (len + 1));
			tmp[x] == NULL ? error_malloc(d, tmp, out, count) : 0;
			ft_strlcpy(tmp[x], &out[start], (len + 1));
			x++;
		}
		start = count[i] + 1;
		i++;
	}
	return (tmp);
}

static void	set_null(t_mini *d, char **out, int **count)
{
	d->arg = (t_arg*)malloc(sizeof(t_arg) * (1));
	d->arg == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	d->arg->c_i = 0;
	d->arg->c = -1;
	d->arg->i = 0;
	d->arg->set = 0;
	d->arg->a = 0;
	(*out) = ft_calloc(PATH_MAX, sizeof(char*));
	(*out) == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	(*count) = ft_calloc(PATH_MAX, sizeof(int*));
	(*count) == NULL ? error_malloc(d, NULL, (*out), NULL) : 0;
	d->arg->count = ft_calloc(PATH_MAX, sizeof(int*));
	d->arg->count == NULL ? error_malloc(d, NULL, (*out), *count) : 0;
}

static int	split_command(t_mini *d, char *line, int *count)
{
	char	*out;

	set_null(d, &out, &count);
	upgrade_line(d->arg, line, out, count);
	d->orig = split_line(d, out, count);
	free(out);
	free(count);
	update_array(d);
	return (1);
}

void		commands(t_mini *d, char *line)
{
	char	**cmd;
	int		i;
	int		*count;

	i = 0;
	if (syntax_check(d, line) == -1)
	{
		free(line);
		return ;
	}
	count = ft_calloc(PATH_MAX, sizeof(int*));
	count == NULL ? error_malloc(d, NULL, line, NULL) : 0;
	cmd = line_split(d, line, count, ';');
	free(line);
	while (cmd[i])
	{
		split_command(d, cmd[i], count);
		if (d->orig[0])
			pipes(d);
		ft_free(d->orig);
		free(d->arg->count);
		free(d->arg);
		i++;
	}
	ft_free(cmd);
}
