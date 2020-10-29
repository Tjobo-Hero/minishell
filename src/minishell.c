/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:13:23 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:13:26 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	screen_clean(void)
{
	write(1, "\e[1;1H\e[2J", 11);
}

static void	block_ctrl_c(int sig)
{
	g_ret = 1;
	ft_putstr_fd("\n\x1b[;01mminishell>\x1b[;37m ", 1);
	(void)sig;
}

static void	block_ctrl_slash(int sig)
{
	(void)sig;
}

static void	start_mini(t_mini *d)
{
	if (d->is_child == 2)
		ft_putstr_fd("\x1b[34;01mQuit: 3\n\x1b[;01mminishell>\x1b[;37m ", 1);
	if (d->is_child == 1 || d->is_child == 2)
	{
		g_ret = 0;
		d->is_child = 0;
	}
	else
		ft_putstr_fd("\x1b[;01mminishell>\x1b[;37m ", 1);
}

int			main(void)
{
	t_mini	d;
	char	*line;

	struct_null(&d);
	init_env(&d);
	screen_clean();
	while (1)
	{
		signal(SIGINT, block_ctrl_c);
		signal(SIGQUIT, block_ctrl_slash);
		start_mini(&d);
		if (!get_next_line(0, &line))
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		d.ret += g_ret;
		g_ret = 0;
		commands(&d, line);
	}
	return (0);
}
