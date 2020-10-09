/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:08:37 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/09 13:50:26 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		**update_env(t_mini *d)
{
	t_env	*check;
	int		i;

	check = look_up("PWD", d->echo);
	if (check == NULL)
		return (0);
	d->cwd = create_str(PATH_MAX);
	// PROTECTION
	getcwd(d->cwd, sizeof(d->cwd));
	// PROTECTION
	i = ft_strlen(d->cwd);
	free(check->list);
	check->list = malloc(sizeof(char*) * (i + 1));
	ft_strlcpy(check->list, d->cwd, i + 1);
	check->echo = check->list;
	free(d->cwd);
	return ((int**)0);
}

char	*get_user(t_mini *d)
{
	t_env	*tmp;

	tmp = look_up("HOME", d->echo);
	if (tmp == NULL)
		return (NULL);
	return (tmp->list);
}

int		**error_return(t_mini *d)
{
	t_env	*tmp;

	tmp = look_up("HOME", d->echo);
	if (tmp == NULL)
		ft_printf("bash: cd: HOME not set\n");
	else
		ft_printf("bash: cd: %s: %s\n", d->args[1], strerror(errno));
	return ((int**)0);
}

int		**cd(t_mini *d)
{
	if (d->args[1] == NULL)
	{
		if (chdir(get_user(d)))
			return (error_return(d));
		return (update_env(d));
	}
	if (ft_strncmp(d->args[1], "~", ft_strlen(d->args[1])) == 0)
	{
		if (chdir(get_user(d)))
			return (error_return(d));
		return (update_env(d));
	}
	if (chdir(d->args[1]))
		return (error_return(d));
	return (update_env(d));
}
