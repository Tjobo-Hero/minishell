/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:08:37 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/16 18:37:46 by rbraaksm      ########   odam.nl         */
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
	getcwd(d->cwd, sizeof(d->cwd));
	i = ft_strlen(d->cwd);
	clear_str(d->list[check->index].list);
	clear_str(d->list[check->index].echo);
	ft_strlcpy(d->list[check->index].list, d->cwd, i + 1);
	ft_strlcpy(d->list[check->index].echo, d->cwd, i + 1);
	return (0);
}

char	*get_user(t_mini *d)
{
	t_env	*tmp;

	tmp = look_up("HOME", d->echo);
	if (tmp == NULL)
		return (NULL);
	return (tmp->list);
}

int		**error_return(t_mini *d, int i)
{
	if (i == 0)
		ft_printf("%s\n", "cd: too many arguments");
	else if (i == 1)
		ft_printf("bash: cd: %s: %s\n", d->args[1], strerror(errno));
	return ((int**)1);
}

int		**cd(t_mini *d)
{
	if (d->args[1] == NULL)
	{
		if (chdir(get_user(d)))
			return (error_return(d, 1));
		return (update_env(d));
	}
	if (d->c_arg >= 3)
		return (error_return(d, 0));
	if (ft_strncmp(d->args[1], "~", ft_strlen(d->args[1])) == 0)
	{
		if (chdir(get_user(d)))
			return (error_return(d, 1));
		return (update_env(d));
	}
	if (chdir(d->args[1]))
		return (error_return(d, 1));
	return (update_env(d));
}
