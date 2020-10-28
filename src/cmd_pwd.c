/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 15:06:22 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/28 16:57:41 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			**cmd_pwd(t_mini *d)
{
	char	*return_ptr;
	char	*cwd;

	cwd = ft_calloc(PATH_MAX, sizeof(char*));
	cwd == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	return_ptr = getcwd(cwd, PATH_MAX);
	if (return_ptr == NULL)
	{
		print_error("bash: pwd: ", strerror(errno), NULL, NULL);
		return ((int**)1);
	}
	ft_write(d, cwd);
	ft_write(d, "\n");
	free(cwd);
	return (0);
}
