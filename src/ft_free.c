/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:12:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/08 10:52:39 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_mini *d, char **args, int i)
{
	int	x;

	x = d->c_pipe;
	while (x > 0 && i == 1)
	{
		free(d->pipes[x - 1]);
		x--;
	}
	if (i == 1 && d->pipes != NULL)
		free(d->pipes);
	i = (i == 1 ? d->c_arg : d->c_cmd);
	while (i > 0)
	{
		free(args[i - 1]);
		i--;
	}
	free(args);
}

void	free_environ(char **environ)
{
	int		i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	while (i > 0)
	{
		free(environ[i - 1]);
		i--;
	}
	free(environ);
}
