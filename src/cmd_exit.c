/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/12 15:22:40 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/10/12 18:14:41 by tvan-cit      ########   odam.nl         */
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
	if (d->args[1] && d->args[2])
	{
		ft_printf("bash: exit: too many arguments\n");
		exit(0);
	}
	while (d->args[1][index])
	{
		if (ft_isdigit(d->args[1][index]) == 0)
		{
			ft_printf("bash: exit: %s: numeric argument required\n",
			d->args[1]);
			exit(0);
		}
		index++;
	}
	exit_number = ft_atoi(d->args[1]);
	exit(exit_number);
}
