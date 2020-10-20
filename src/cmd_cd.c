/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:08:37 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/20 14:34:36 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(t_mini *d, t_env *new)
{
	t_env	*old;

	int	i;

	old = look_up("OLDPWD", d->echo);
	if (old == NULL)
		return ;
	free(old->list);
	i = ft_strlen(new->list);
	old->list = malloc(sizeof(char*) * (i + 1));
	old->list == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	ft_strlcpy(old->list, new->list, (i + 1));
	old->echo = old->list;
}

int		**update_env(t_mini *d)
{
	t_env	*new;
	int		i;
	char	*return_ptr;
	char	*cwd;

	new = look_up("PWD", d->echo);
	if (new == NULL)
		return (0);
	update_oldpwd(d, new);
	cwd = ft_calloc(PATH_MAX, sizeof(char*));
	cwd == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	return_ptr = getcwd(cwd, PATH_MAX);
	if (return_ptr == NULL)
	{
		ft_printf("bash: pwd: %s\n", strerror(errno));
		return ((int**)1);
	}
	i = ft_strlen(cwd);
	free(new->list);
	new->list = malloc(sizeof(char*) * (i + 1));
	new->list == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	ft_strlcpy(new->list, cwd, (i + 1));
	new->echo = new->list;
	free(cwd);
	return ((int**)0);
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

int		**cmd_cd(t_mini *d)
{
	t_env	*tmp;
	char	*user;

	tmp = look_up("HOME", d->echo);
	if (tmp == NULL)
		user = NULL;
	else
		user = tmp->list;
	if (d->args[1] == NULL ||
		(ft_strncmp(d->args[1], "~", ft_strlen(d->args[1])) == 0))
	{
		if (chdir(user))
			return (error_return(d));
		return (update_env(d));
	}
	if (chdir(d->args[1]))
		return (error_return(d));
	return (update_env(d));
}
