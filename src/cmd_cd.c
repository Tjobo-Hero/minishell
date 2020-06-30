/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:08:37 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/06/30 16:28:54 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(t_mini *d)
{
	int		i;

	i = 0;
	while (d->env[i])
	{
		if (!ft_strncmp(d->env[i], "PWD", 3) && d->env[i][3] == '=')
			break ;
		i++;
	}
	clear_str(d->env[i]);
	ft_strlcat(d->env[i], "PWD=", 5);
	ft_strlcat(d->env[i], d->cwd, ft_strlen(d->cwd) + 5);
}

char	*get_user(t_mini *d, int c)
{
	char	*user;
	char	*tmp;
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
	if (user == NULL)
		return (NULL);
	tmp = user;
	if (c == 0)
		free(user);
	return (tmp);
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
	update_env(d);
	if (d->args[1] == NULL)
	{
		if (chdir(get_user(d, 0)))
			return (error_return(d, 1));
		return (0);
	}
	if (d->c_arg >= 3)
		return (error_return(d, 0));
	d->args[1][0] == '~' ? d->args[1] = get_user(d, 1) : 0;
	if (chdir(d->args[1]))
		return (error_return(d, 1));
	return (0);
}
