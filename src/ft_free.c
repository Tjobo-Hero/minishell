/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:12:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/06/25 12:07:48 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_mini *d, char **args, int i)
{
	i = (i == 1 ? d->c_arg : d->c_cmd);
	while (i > 0)
	{
		free(args[i - 1]);
		i--;
	}
	free(args);
}
