/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:08:37 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/09 13:58:00 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_str(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = '\0';
		i++;
	}
}

// int		**update_env(t_mini *d)
// {
// 	int		i;

// 	i = 0;
// 	getcwd(d->cwd, sizeof(d->cwd));
// 	while (d->env[i])
// 	{
// 		if (!ft_strncmp(d->env[i], "PWD", 3) && d->env[i][3] == '=')
// 			break ;
// 		i++;
// 	}
// 	clear_str(d->env[i]);
// 	ft_strlcat(d->env[i], "PWD=", 5);
// 	ft_strlcat(d->env[i], d->cwd, ft_strlen(d->cwd) + 5);
// 	return (0);
// }

char	*get_user(t_mini *d)
{
	t_env	*tmp;

	tmp = look_up("HOME", d->echo);
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
		return (0);
		// return (update_env(d));
	}
	if (d->c_arg >= 3)
		return (error_return(d, 0));
	if (ft_strncmp(d->args[1], "~", ft_strlen(d->args[1])) == 0)
	{
		if (chdir(get_user(d)))
			return (error_return(d, 1));
		return (0);
	}
	if (chdir(d->args[1]))
	 		return (error_return(d, 1));
	return (0);
	// return (update_env(d));
}
