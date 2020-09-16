/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 10:47:29 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/16 11:51:34 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_pipes2(t_mini *d, int c)
{
	int		i;
	int		start;

	i = 0;
	start = (c == 0) ? 0 : d->count_pipe[c - 1] + 1;
	while (start < d->count_pipe[c])
	{
		printf("ARG[%d]:\t%s\n", i, d->args[start]);
		start++;
		i++;
	}
	printf("--------------------------\n");
	return ;
}

void	do_pipes(t_mini *d, int c)
{
	do_pipes2(d, c);
	if (d->count_pipe[c + 1] != 0)
		do_pipes(d, c + 1);
}
