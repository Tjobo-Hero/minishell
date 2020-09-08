/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/09/08 10:51:03 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	screen_clean(void)
{
	write(1, "\e[1;1H\e[2J", 11);
}

int		create_str(t_mini *d, char *arg)
{
	char	*tmp;
	int		i;

	i = ft_strlen(arg);
	tmp = malloc(sizeof(char *) * (i + 1));
	make_string(d, arg, tmp);
	ft_bzero(arg, i);
	ft_strlcpy(arg, tmp, ft_strlen(tmp) + 1);
	free(tmp);
	return (1);
}

void	set_arguments_correct(t_mini *d, int set)
{
	d->c_arg = set;
	while (d->args[set])
	{
		free(d->args[set]);
		d->args[set] = NULL;
		set++;
	}
}

void	find_pipes(t_mini *d)
{
	int	i;
	int	x;
	int	set;

	i = 0;
	x = 0;
	d->pipes = NULL;
	while (d->args[i] && ft_strncmp(d->args[i], "|", 1) != 0)
		i++;
	if (!d->args[i])
		return ;
	i++;
	set = i;
	d->pipes = malloc(sizeof(char **) * (d->c_arg - i) + 1);
	while (i < d->c_arg)
	{
		d->pipes[x] = ft_strdup(d->args[i]);
		x++;
		i++;
	}
	d->pipes[x] = NULL;
	d->c_pipe = x;
	set_arguments_correct(d, set - 1);
}

void	get_commands(t_mini *d)
{
	int	i;
	int	count[PATH_MAX];
	int	x;

	i = 0;
	x = 0;
	d->c_cmd = new_count_commands(d->line, count, ';');
	d->cmd = new_fill_commands(d->line, count, d->c_cmd);
	while (i < PATH_MAX && i < d->c_cmd)
	{
		d->c_arg = new_count_commands(d->cmd[i], count, ' ');
		d->args = new_fill_commands(d->cmd[i], count, d->c_arg);
		while (d->args[x])
			x += create_str(d, d->args[x]);
		find_pipes(d);
		run_commands(d);
		ft_free(d, d->args, 1);
		i++;
	}
	ft_free(d, d->cmd, 0);
}

int		main(void)
{
	t_mini	d;

	init_env(&d);
	screen_clean();
	while (1)
	{
		write(1, "minishell> ", 11);
		if (!(get_next_line(0, &d.line)))
			return (0);
		if (ft_strncmp(d.line, "\n", ft_strlen(d.line)) != 0)
			get_commands(&d);
		free(d.line);
	}
	return (0);
}
