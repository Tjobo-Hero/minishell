/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 17:29:09 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/24 11:36:52 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	pipes_init(t_mini *d, int count)
// {
// 	int	i;

// 	i = 0;
// 	d->pids = 0;
// 	d->pipes = ft_calloc(count, sizeof(int *));
// 	if (d->pipes == NULL)
// 		exit(1);
// 	while (i + 1 < count)
// 	{
// 		d->pipes[i] = ft_calloc(3, sizeof(int));
// 		if (d->pipes[i] == NULL)
// 			exit(1);
// 		if (pipe(d->pipes[i]) == -1)
// 			exit(1);
// 		i++;
// 	}
// }

// void	find_pipes(t_mini *d)
// {
// 	int		i;

// 	i = 0;
// 	while (d->split_line[i])
// 		i++;
// 	if (i != 0)
// 		pipes_init(d, i + 1);
// 	pipes(d, 0);
// }
