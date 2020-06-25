/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:08:37 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/06/25 15:46:46 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_user(t_mini *d)
{
	char	*user;
	int		i;

	i = 0;
	free(d->args[1]);
	while (d->env[i] != '\0')
	{
		if (!ft_strncmp(d->env[i], "HOME", 4) && d->env[i][4] == '=')
			break ;
		i++;
	}
	user = ft_strdup(&d->env[i][5]);
	return (user);
}

char	**cd(t_mini *d)
{
	if (d->args[1] == NULL)
		return (NULL);
	if (d->c_arg >= 3)
	{
		ft_printf("%s\n", "cd: too many arguments");
		return (NULL);
	}
	d->args[1][0] == '~' ? d->args[1] = get_user(d) : 0;
	if (chdir(d->args[1]))
	{
		ft_printf("%s: %s: ", d->args[0], d->args[1]);
		perror("");
		return (NULL);
	}
	return (NULL);
}
