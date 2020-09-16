/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/09/16 16:39:52 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	screen_clean(void)
{
	write(1, "\e[1;1H\e[2J", 11);
}

int		*pipes_init(int *count, int i, int x)
{
	int	*tmp;
	int	len;

	tmp = ft_calloc((x), sizeof(count));
	len = 0;
	while (count[len] != 0)
	{
		tmp[len] = count[len];
		len++;
	}
	tmp[len] = i;
	free(count);
	return (tmp);
}

void	pipes_init2(t_mini *d, int count)
{
	int	i;

	i = 0;
	// p->pids = 0;
	d->pipes = ft_calloc(count, sizeof(int *));
	if (d->pipes == NULL)
		exit(1);
	while (i + 1 < count)
	{
		d->pipes[i] = ft_calloc(3, sizeof(int));
		if (d->pipes[i] == NULL)
			exit(1);
		if (pipe(d->pipes[i]) == -1)
			exit(1);
		// printf("PIPE: %d\n", *d->pipes[i]);
		i++;
	}
}

void	find_pipes(t_mini *d)
{
	int		i;
	int		x;
	int		*count;

	i = 0;
	x = 0;
	count = ft_calloc((x + 1), sizeof(int));
	while (d->tmp_args[i])
	{
		if (ft_strncmp(d->tmp_args[i], "|", 1) == 0)
		{
			count = pipes_init(count, i, x + 1);
			x++;
		}
		i++;
	}
	count[x] = i;
	count[x + 1] = 0;
	if (x != 0)
		pipes_init2(d, x + 1);
	i = 0;
	while (count[i] != 0)
	{
		printf("COUNT:\t%d\n", count[i]);
		i++;
	}
	pipes(d, 0, count);
	free(count);
}

void	get_commands(t_mini *d, char *line)
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
		new_split(d, cmd[i]);
		find_pipes(d);
		ft_free(d->tmp_args);
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
