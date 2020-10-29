/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:07:53 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:07:57 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			**cmd_exit(t_mini *d)
{
	int	exit_number;
	int	index;

	index = 0;
	if (!d->forked && d->args[1] == NULL)
		exit(0);
	while (d->args[1][index])
	{
		if (ft_isdigit(d->args[1][index]) == 0)
		{
			print_error("bash: exit: ", d->args[1],
			" numeric argument required", NULL);
			exit(0);
		}
		index++;
	}
	if (d->args[1] && d->args[2])
	{
		print_error("exit\nbash: exit: too many arguments", NULL, NULL, NULL);
		return (0);
	}
	exit_number = ft_atoi(d->args[1]);
	exit(exit_number);
}
