/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/09/03 09:12:02 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	screen_clean(void)
{
	write(1, "\e[1;1H\e[2J", 11);
}

void	get_commands(t_mini *d)
{
	int	i;
	int	count[PATH_MAX];

	i = 0;
	d->c_cmd = new_count_commands(d->line, count, ';');
	d->cmd = new_fill_commands(d->line, count, d->c_cmd);
	while (i < PATH_MAX && i < d->c_cmd)
	{
		d->c_arg = new_count_commands(d->cmd[i], count, ' ');
		d->args = new_fill_commands(d->cmd[i], count, d->c_arg);
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
