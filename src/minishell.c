/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/09/11 13:06:27 by rbraaksm      ########   odam.nl         */
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

void	pipes_init(t_mini *d)
{
	int	i;

	i = 0;
	if (d->c_pipe == 0)
		return ;
	d->pipe = ft_calloc(d->c_pipe, sizeof(int *));
	if (d->pipe == NULL)
		exit(1);
	while ((i + 1) < d->c_pipe)
	{
		d->pipe[i] = ft_calloc(3, sizeof(int *));
		if (d->pipe[i] == NULL)
			exit(1);
		if (pipe(d->pipe[i]) == -1)
			exit(1);
		printf("PIPE: %d\n", *d->pipe[i]);
		i++;
	}
}

// void	find_pipes(t_mini *d)
// {
// 	int	i;
// 	int	x;
// 	int	set;

// 	i = 0;
// 	x = 0;
// 	d->pipes = NULL;
// 	d->c_pipe = new_count_commands()
	// while (d->args[i] && ft_strncmp(d->args[i], "|", 1) != 0)
	// 	i++;
	// if (!d->args[i])
	// 	return ;
	// i++;
	// set = i;
	// d->pipes = malloc(sizeof(char **) * (d->c_arg - i) + 1);
	// while (i < d->c_arg)
	// {
	// 	d->pipes[x] = ft_strdup(d->args[i]);
	// 	x++;
	// 	i++;
	// }
	// d->pipes[x] = NULL;
	// d->c_pipe = x - 1;
	// set_arguments_correct(d, set - 1);
	// pipes_init(d);
// }

// char	**split_pipes(t_mini *d)
// {
// 	char	**tmp;
// 	int		i;
// 	int		x;
// 	int		z;
// 	int		count[PATH_MAX];

// 	i = 0;
// 	while (d->args[i])
// 	{
// 		printf("ARG:\t%s", d->args[i]);
// 		x = new_count_commands(d->args[i], count, '|');
// 			printf("\n");
// 		if (x > 1)
// 		{
// 			printf("  -->  found pipe\tx: %d\n", x);
// 			tmp = new_fill_commands(d->args[i], count, x);
// 			z = 0;
// 			while (tmp[z])
// 			{
// 				printf("ARG2:\t%s\n", tmp[z]);
// 				z++;
// 			}
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

void	get_commands(t_mini *d, char *line)
{
	// char	**cmd;
	// int		c_cmd;
	// int		i;
	// int		count[PATH_MAX];

	new_split(d, line);
	// i = 0;
	// c_cmd = new_count_commands(line, count, ';');
	// cmd = new_fill_commands(line, count, c_cmd);
	// 	clear_str(d->new.nw_tmp);
		// make_string(d, line, d->new.nw_tmp);
	// 	printf("Line:\t%s\n", line);
	// 	printf("TMP:\t%s\n", d->new.nw_tmp);
	// while (i < PATH_MAX && i < c_cmd)
	// {
	// 	printf("CMD:\t%s\n", cmd[i]);
	// 	d->c_arg = new_count_commands(cmd[i], count, ' ');
	// 	d->args = new_fill_commands(cmd[i], count, d->c_arg);
	// 	// ft_strtrim(d->args[0], "|");
	// 	// int x = 0;
	// 	// while (d->args[x])
	// 	// {
	// 		char *tmp;
	// 		// tmp = ft_strnstr(d->args[0], "|", ft_strlen(d->args[0]));
	// 		tmp = ft_strtrim(d->args[0], "|");
	// 		printf("ARG:\t%s\n", d->args[0]);
	// 		printf("TMP:\t%s\n", tmp);
	// 	// 	x++;
	// 	// }
	// 	// create_str(d);
	// 	// find_pipes(d);
	// 	// run_commands(d);
	// 	ft_free(d->args);
	// 	i++;
	// }
	// ft_free(cmd);
	// free(line);
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
