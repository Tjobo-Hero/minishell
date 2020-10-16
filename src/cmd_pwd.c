/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 15:06:22 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/15 18:42:49 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**pwd(t_mini *d)
{
	char	*return_ptr;

	d->cwd = ft_calloc(PATH_MAX, sizeof(char*));
	d->cwd == NULL ? malloc_error() : 0;
	return_ptr = getcwd(d->cwd, PATH_MAX);
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
