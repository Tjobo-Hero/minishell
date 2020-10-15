/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_init.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 17:23:46 by rbraaksm      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/10/13 14:17:01 by tvan-cit      ########   odam.nl         */
=======
/*   Updated: 2020/10/12 11:34:38 by tvan-cit      ########   odam.nl         */
>>>>>>> 7877c706e2e3d0ea0493ee2ab28b78b9018d4f18
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
<<<<<<< HEAD
	//PROTECTION
	d->orig = (char**)malloc(sizeof(char*) * (total_tmp(out, count) + 1));
	//PROTECTION
=======
	d->orig = (char**)malloc(sizeof(char*) * (total_tmp(out, count) + 1));
>>>>>>> 7877c706e2e3d0ea0493ee2ab28b78b9018d4f18
	while (count[i] != 0)
	{
		len = count[i] - start;
		if (out[start] != '|')
		{
			d->split_line[x] = malloc(sizeof(char*) * len + 1);
			//PROTECTION
			ft_strlcpy(d->split_line[x], &out[start], len + 1);
			d->orig[x] = ft_strdup(d->split_line[x]);
<<<<<<< HEAD
			//PROTECTION
			// printf("ORG_SPLIT_LINE:\t%s\n", d->orig[x]);
=======
>>>>>>> 7877c706e2e3d0ea0493ee2ab28b78b9018d4f18
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
	ft_bzero(out, PATH_MAX);
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
	if (count == NULL)
		exit(1);
	c_cmd = new_count_commands(line, count, ';');
	// Protection
	cmd = new_fill_commands(line, count, c_cmd);
<<<<<<< HEAD
	// Protection
=======
>>>>>>> 7877c706e2e3d0ea0493ee2ab28b78b9018d4f18
	while (cmd && cmd[i])
	{
		split_command(d, cmd[i], count);
		if (d->split_line[0])
		{
			pipes(d);
			ft_free(d->split_line);
			ft_free(d->orig);
<<<<<<< HEAD
			free(count);			// STOND UIT
=======
			// free(count);
>>>>>>> 7877c706e2e3d0ea0493ee2ab28b78b9018d4f18
			free(d->arg->count);
		}
		i++;
	}
	ft_free(cmd);
}
