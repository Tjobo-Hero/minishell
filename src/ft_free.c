/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:12:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/24 13:16:48 by rbraaksm      ########   odam.nl         */
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

void	free_int_array(int **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	arr = NULL;
}
