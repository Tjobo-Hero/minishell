/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:15:14 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:15:16 by rbraaksm      ########   odam.nl         */
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
