/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/09/30 15:08:45 by rbraaksm      ########   odam.nl         */
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

int		main(void)
{
	t_mini	d;
	char	*line;

	init_env(&d);
	// screen_clean();
	while (1)
	{
	// 	signal(SIGINT, block_ctrl_c);
	// 	signal(SIGQUIT, block_ctrl_slash);
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
