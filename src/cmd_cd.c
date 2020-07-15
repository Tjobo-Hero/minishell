/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:08:37 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/15 09:33:22 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	new_lst(t_mini *d, t_env *origin, char *str)
{
	t_env	tmp[1];

	tmp->set = origin->set;
	tmp->index = origin->index;
	tmp->alpha = origin->alpha;
	ft_strlcpy(tmp->head, str, ft_strlen(str) + 1);
	ft_strlcpy(tmp->list, d->cwd, ft_strlen(d->cwd));
	ft_strlcpy(tmp->echo, d->cwd, ft_strlen(d->cwd));
	return (tmp[0]);
}

int		**update_env(t_mini *d)
{
	t_env	*check;
	t_env	tmp[1];
	char	*str;
	int		i;

	i = 0;
	check = look_up("PWD", d->echo);
	if (check == NULL)
		return (0);
	getcwd(d->cwd, sizeof(d->cwd));
	str = ft_strjoin("PWD=", d->cwd);
	delete_lst("PWD", d->echo);
	tmp[0] = new_lst(d, check, "PWD");
	hash_table_insert(&tmp[0], d->echo);
	free(str);
	return (0);
}

char	*get_user(t_mini *d)
{
	t_env	*tmp;

	tmp = look_up("HOME", d->echo);
	/* protection */
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
