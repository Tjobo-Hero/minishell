/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 17:29:09 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/21 18:54:47 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipes_init(t_mini *d, int count)
{
	int	i;

	i = 0;
	// p->pids = 0;
	d->pipes = ft_calloc(count, sizeof(int *));
	if (d->pipes == NULL)
		exit(1);
	while (i + 1 < count)
	{
		d->pipes[i] = ft_calloc(3, sizeof(int));
		if (d->pipes[i] == NULL)
			exit(1);
		if (pipe(d->pipes[i]) == -1)
			exit(1);
		printf("PIPE:\t%d\n", *d->pipes[i]);
		i++;
	}
}

void	find_pipes(t_mini *d)
{
	int		i;

	i = 0;
	while (d->arg->count[i] != 0)
		i++;
	if (i != 0)
		pipes_init(d, i + 1);
	pipes(d, 0, d->arg->count);
}
