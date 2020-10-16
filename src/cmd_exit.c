/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 15:22:40 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/10/16 14:13:34 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			**exit_own(t_mini *d)
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
			ft_putstr_fd("bash: exit: ", 1);
			ft_putstr_fd(d->args[1], 1);
			ft_putstr_fd(" numeric argument required\n", 1);
			exit(0);
		}
		index++;
	}
	if (d->args[1] && d->args[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 1);
		exit(0);
	}
	exit_number = ft_atoi(d->args[1]);
	exit(exit_number);
}