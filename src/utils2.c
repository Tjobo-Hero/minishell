/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 18:46:05 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/26 18:48:42 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_on_off(int *doub, int *single, char c)
{
	if (c == '\"' && *single == -1)
		(*doub) *= -1;
	else if (c == '\'' && *doub == -1)
		(*single) *= -1;
}

void	set_array_null(int *single, int *doub, int *y, int *set)
{
	(*single) = -1;
	(*doub) = -1;
	(*y) = 0;
	(*set) = 0;
}
