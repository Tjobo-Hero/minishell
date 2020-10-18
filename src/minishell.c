/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/10/18 18:51:00 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	screen_clean(void)
{
	write(1, "\e[1;1H\e[2J", 11);
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

void	start_mini(t_mini *d)
{
	if (d->is_child == 2)
		ft_putstr_fd("\x1b[34;01mQuit: 3\n\x1b[35;01mbash-3.3$ \x1b[31;37m", 1);
	if (d->is_child == 1 || d->is_child == 2)
	{
		g_ret = 0;
		d->is_child = 0;
	}
	else
		ft_putstr_fd("\x1b[;01mminishell>\x1b[;37m ", 1);
}

int		main(void)
{
	t_mini	d;
	char	*line;

	struct_null(&d);
	init_env(&d);
	// screen_clean();
	while (1)
	{
		// signal(SIGINT, block_ctrl_c);
		// signal(SIGQUIT, block_ctrl_slash);
		start_mini(&d);
		if (get_next_line(0, &line) < 0)
		{
			ft_printf("exit\n");
			exit(0);
		}
		d.ret += g_ret;
		g_ret = 0;
		if (line)
			get_commands(&d, line);
	}
	return (0);
}
