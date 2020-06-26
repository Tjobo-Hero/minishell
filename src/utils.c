/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 15:55:01 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/26 10:54:37 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		screen_clean(void)
{
	write(1, "\e[1;1H\e[2J", 11);
}

// char	**p_ret(int i, t_mini *d)
// {
// 	d->ret = i;
// 	return (NULL);
// }
