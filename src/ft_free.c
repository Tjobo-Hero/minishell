/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:12:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/06/24 15:41:52 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **args, char *str, char c)
{
	int	i;

	i = count_commands(str, c);
	while (i > 0)
	{
		free(args[i - 1]);
		i--;
	}
	free(args);
}