/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/08/04 22:46:29 by rbraaksm      ########   odam.nl         */
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
	int	x;
	int	count[PATH_MAX];

	i = 0;
	d->c_cmd = new_count_commands(d->line, count, ';');
	d->cmd = new_fill_commands(d->line, count, d->c_cmd, ';');
	while (i < PATH_MAX && i < d->c_cmd)
	{
		x = 0;
		d->c_arg = new_count_commands(d->cmd[i], count, ' ');
		d->args = new_fill_commands(d->cmd[i], count, d->c_arg, ' ');
		// printf("CMD %s\n", d->cmd[i]);
		// while (d->args[x] != NULL)
		// {
		// 	printf("\tARG %s\n", d->args[x]);
		// 	x++;
		// }
		i++;
	}
	run_commands(d);
}

int		main(void)
{
	t_mini	d;

	init_env(&d);
	init_commands(&d);
	screen_clean();
	while (1)
	{
		write(1, "minishell> ", 11);
		if (!(get_next_line(0, &d.line)))
			return (0);
		get_commands(&d);
	}
	return (0);
}
