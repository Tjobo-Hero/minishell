/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:12:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/09 15:16:17 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **args)
{
	int	x;

	x = 0;
	while (args[x])
	{
		free(args[x]);
		x++;
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
