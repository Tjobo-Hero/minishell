/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 15:06:22 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/06/26 10:34:11 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**pwd(t_mini *d)
{
	char	cwd[PATH_MAX];
	char	*return_ptr;

	(void)d;
	return_ptr = getcwd(cwd, sizeof(cwd));
	if (return_ptr == NULL)
	{
		ft_printf("bash: pwd: %s\n", strerror(errno));
		return ((int**)1);
	}
	ft_printf("%s\n", cwd);
	return (0);
}
