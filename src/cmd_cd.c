/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:08:37 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/06/17 14:16:48 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_user(char *cwd)
{
	char	*user;
	int		i;

	i = 1;
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

void	cd(char **cmd)
{
	char	cwd[PATH_MAX];

	if (cmd[1] == NULL || cmd[2])
		return ;
	getcwd(cwd, sizeof(cwd));
	if (ft_strncmp("~", cmd[1], ft_strlen(cmd[1])) == 0)
	{
		free(cmd[1]);
		cmd[1] = get_user(cwd);
	}
	if (chdir(cmd[1]))
	{
		ft_printf("%s: %s: ", cmd[0], cmd[1]);
		perror("");
		return ;
	}
}