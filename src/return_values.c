/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   return_values.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:13:51 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:13:54 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	values(t_mini *d, int wait)
{
	if (WIFEXITED(wait))
		d->ret = WEXITSTATUS(wait);
	if (WIFSIGNALED(wait))
	{
		d->ret = WTERMSIG(wait);
		if (d->ret == 2)
		{
			d->ret = 130;
			d->is_child = 1;
		}
		if (d->ret == 3)
		{
			d->ret = 131;
			d->is_child = 2;
		}
	}
}

void		return_values(t_mini *d)
{
	int x;
	int wait;

	wait = 0;
	x = 0;
	while (x < d->pids)
	{
		waitpid(-1, &wait, 0);
		values(d, wait);
		x++;
	}
	free_int_array(d->pipes);
}
