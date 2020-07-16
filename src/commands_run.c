/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:01:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/16 18:39:11 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_command(int i)
{
	char	*command[6];

	command[0] = "pwd";
	command[1] = "cd";
	command[2] = "export";
	command[3] = "env";
	command[4] = "unset";
	// command[15] = "exit";
	// command[18] = "echo";
	command[5] = NULL;
	return (command[i]);
}

int		**(*start_command(int i))(t_mini *d)
{
	int	**(*command[5])(t_mini *d);

	command[0] = &pwd;
	command[1] = &cd;
	command[2] = &export;
	command[3] = &env;
	command[4] = &unset;
	return (command[i]);
}

int		**run_commands(t_mini *d)
{
	int		i;
	int		len;

	i = 0;
	check_single_double(d);
	len = ft_strlen(d->args[0]);
	while (i < 5)
	{
		if (!ft_strncmp(d->args[0], find_command(i), len))
		{
			d->ret = (int)start_command(i)(d);
			return (0);
		}
		i++;
	}
	execute(d, d->args);
	return (0);
}
