/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 15:06:22 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/06/25 16:17:51 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**pwd(t_mini *d)
{
	char	cwd[PATH_MAX];
	char	*return_ptr;

	return_ptr = getcwd(cwd, sizeof(cwd));
	if (return_ptr == NULL)
	{
		ft_printf("bash: pwd: %s\n", strerror(errno));
		return (p_ret(1, d));
	}
	ft_printf("%s\n", cwd);
	return (p_ret(0, d));
}
