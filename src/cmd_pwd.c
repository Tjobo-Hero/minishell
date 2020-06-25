/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 15:06:22 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/06/25 15:21:37 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**pwd(t_mini *d)
{
	ft_printf("%s\n", d->cwd);
    return (NULL);
}
