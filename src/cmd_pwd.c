/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 15:06:22 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/13 14:19:24 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**pwd(t_mini *d)
{
	// char	*cwd;
	char	*return_ptr;

	d->cwd = create_str(PATH_MAX);
	return_ptr = getcwd(d->cwd, PATH_MAX);
	// printf("RETURN_PTR: \t%s\n", return_ptr);
	if (return_ptr == NULL)
	{
		ft_printf("bash: pwd: %s\n", strerror(errno));
		return ((int**)1);
	}
	ft_write(d->fd, d->cwd);
	ft_write(d->fd, "\n");
	free(d->cwd);
	return (0);
}
