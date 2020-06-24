/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:08:37 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/06/24 17:15:43 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_user(char *cwd)
{
	char	*user;
	int		i;
	int		count;

	i = 1;
	count = 0;
	while (cwd[i] != '/')
		i++;
	i++;
	while (cwd[i] != '/')
		i++;
	i++;
	user = malloc(sizeof(char *) + i);
	ft_strlcpy(user, cwd, i);
	return (user);
}

void	cd(t_mini *d)
{
	if (d->args[1] == NULL || d->args[2])
		return ;
	/* User uit de env halen? */
	if (ft_strncmp("~", d->args[1], ft_strlen(d->args[1])) == 0)
	{
		free(d->args[1]);
		d->args[1] = get_user(d->cwd);
	}
	if (chdir(d->args[1]))
	{
		ft_printf("%s: %s: ", d->args[0], d->args[1]);
		perror("");
		return ;
	}
}
