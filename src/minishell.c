/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/09/16 11:47:41 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	screen_clean(void)
{
	write(1, "\e[1;1H\e[2J", 11);
}

int		create_str(t_mini *d)
{
	char	*tmp;
	int		i;
	int		x;

	x = 0;
	while (d->args[x])
	{
		i = ft_strlen(d->args[x]);
		tmp = malloc(sizeof(char *) * (i + 1));
		make_string(d, d->args[x], tmp);
		ft_bzero(d->args[x], i);
		ft_strlcpy(d->args[x], tmp, ft_strlen(tmp) + 1);
		free(tmp);
		x++;
	}
	return (1);
}

void	set_arguments_correct(t_mini *d)
{
	int		i;

	i = 0;
	while (d->args[i] && ft_strncmp(d->args[i], "|", 1) != 0)
		i++;
	free(d->args[i]);
	d->args[i] = NULL;
	i++;
	while (d->args[i])
	{
		free(d->args[i]);
		i++;
	}
}

void	pipes_init(t_mini *d)
{
	int	i;

	i = 0;
	if (d->c_pipe == 0)
		return ;
	d->pipe = ft_calloc(d->c_pipe, sizeof(int *));
	if (d->pipe == NULL)
		exit(1);
	while (i < d->c_pipe)
	{
		d->pipe[i] = ft_calloc(3, sizeof(int *));
		if (d->pipe[i] == NULL)
			exit(1);
		if (pipe(d->pipe[i]) == -1)
			exit(1);
		i++;
	}
}

char	*make_pipe_str(t_mini *d, int *i)
{
	char	*new;
	char	*tmp;

	(*i)++;
	tmp = ft_strdup("");
	while (d->args[*i] != NULL && ft_strncmp(d->args[*i], "|", 1) != 0)
	{
		new = tmp;
		free(tmp);
		tmp = ft_strjoin(new, d->args[*i]);
		if (d->args[*i + 1] != NULL && ft_strncmp(d->args[*i + 1], "|", 1) != 0)
		{
			new = tmp;
			free(tmp);
			tmp = ft_strjoin(new, " ");
		}
		(*i)++;
	}
	return (tmp);
}

void	find_pipes(t_mini *d)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	d->c_pipe = 0;
	// d->pipes = NULL;
	count_init(d->count_pipe);
	while (d->args[i])
	{
		if (ft_strncmp(d->args[i], "|", 1) == 0)
		{
			d->count_pipe[d->c_pipe] = i;
			d->c_pipe++;
		}
		i++;
	}
	if (d->c_pipe == 0)
		return ;
	d->count_pipe[d->c_pipe] = i;
	while (d->count_pipe[x] != 0)
	{
		printf("COUNT:\t%d\n", d->count_pipe[x]);
		x++;
	}
	printf("------------------\n\n");
	// d->pipes = malloc(sizeof(char**) * (d->c_pipe + 1));
	// i = 0;
	// while (d->args[i])
	// {
	// 	if (ft_strncmp(d->args[i], "|", 1) == 0)
	// 	{
	// 		d->pipes[x] = make_pipe_str(d, &i);
	// 		x++;
	// 	}
	// 	else
	// 		i++;
	// }
	// d->pipes[x] = NULL;
	// set_arguments_correct(d);
	pipes_init(d);
}


void	get_commands(t_mini *d, char *line)
{
	char	**cmd;
	int		c_cmd;
	int		i;
	int		count[PATH_MAX];
	int		c;

	i = 0;
	c_cmd = new_count_commands(line, count, ';');
	cmd = new_fill_commands(line, count, c_cmd);
	while (i < PATH_MAX && i < c_cmd)
	{
		c = 0;
		new_split(d, cmd[i]);
		find_pipes(d);
		do_pipes(d, c);
		// run_commands(d);
		ft_free(d->args);
		// ft_free(d->pipes);
		i++;
	}
	ft_free(cmd);
	free(line);
}

void		block_ctrl_c(int sig)
{
	g_ret = 1;
	write(1, "\nminishell> ", 11);
	(void)sig;
}

void		block_ctrl_slash(int sig)
{
	(void)sig;
}

int		main(void)
{
	t_mini	d;
	char	*line;

	init_env(&d);
	screen_clean();
	while (1)
	{
		signal(SIGINT, block_ctrl_c);
		signal(SIGQUIT, block_ctrl_slash);
		write(1, "minishell> ", 11);
		if (!get_next_line(0, &line))
		{
			ft_printf("exit\n");
			exit(0);
		}
		if (ft_strncmp(line, "\n", ft_strlen(line)) != 0)
			get_commands(&d, line);
	}
	return (0);
}
