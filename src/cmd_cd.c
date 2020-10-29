/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:01:16 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 13:09:51 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(t_mini *d, t_env *new)
{
	t_env	*old;
	int		i;

	old = look_up("OLDPWD", d->echo);
	if (old == NULL)
		return ;
	free(old->list);
	free(old->echo);
	i = ft_strlen(new->list);
	old->list = malloc(sizeof(char*) * (i + 1));
	old->list == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	ft_strlcpy(old->list, new->list, (i + 1));
	old->echo = ft_strdup(old->list);
}

int		**update_env(t_mini *d)
{
	t_env	*new;
	char	*return_ptr;

	new = look_up("PWD", d->echo);
	if (new == NULL)
		return (0);
	update_oldpwd(d, new);
	d->cwd = ft_calloc(PATH_MAX, sizeof(char*));
	d->cwd == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	return_ptr = getcwd(d->cwd, PATH_MAX);
	if (return_ptr == NULL)
	{
		print_error("bash: pwd: ", strerror(errno), NULL, NULL);
		return ((int**)1);
	}
	free(new->list);
	free(new->echo);
	new->list = malloc(sizeof(char*) * (ft_strlen(d->cwd) + 1));
	new->list == NULL ? error_malloc(d, NULL, d->cwd, NULL) : 0;
	ft_strlcpy(new->list, d->cwd, (ft_strlen(d->cwd) + 1));
	free(d->cwd);
	new->echo = ft_strdup(new->list);
	new->echo == NULL ? error_malloc(d, NULL, d->cwd, NULL) : 0;
	return ((int**)0);
}

int		**error_return(t_mini *d)
{
	t_env	*tmp;

	tmp = look_up("HOME", d->echo);
	if (tmp == NULL)
		print_error("bash: cd: HOME not set", NULL, NULL, NULL);
	else
		print_error("bash: cd: ", d->args[1], ": ", strerror(errno));
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
