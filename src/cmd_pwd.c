/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 15:06:22 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/06/18 14:46:41 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd()
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	ft_printf("%s\n", cwd);
}
