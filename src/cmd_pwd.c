/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 15:06:22 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/06/25 15:53:55 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pwd(t_mini *d)
{
	char	cwd[PATH_MAX];
	char	*return_ptr;

	return_ptr = getcwd(cwd, sizeof(cwd));
	if (return_ptr == NULL)
	{
		ft_printf("bash: pwd: %s\n", strerror(errno));
		d->ret = 1;
		return (0);
	}
	ft_printf("%s\n", cwd);
	return (0);
}
