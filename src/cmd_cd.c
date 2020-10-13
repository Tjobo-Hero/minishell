/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:08:37 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/13 14:52:03 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		**update_env(t_mini *d)
{
	t_env	*check;
	int		i;
	char	*return_ptr;

	check = look_up("PWD", d->echo);
	if (check == NULL)
		return (0);
	d->cwd = create_str(PATH_MAX); // WEET NIET OF HET NOG PROTECITON NODIG HEEFT AANGEZIEN DIE NU OOK IN DE FUNCTIE ZIT
	// if (d->cwd == NULL)
	// 	return (0);
	return_ptr = getcwd(d->cwd, PATH_MAX);    // BIJ PATH_MAX stond eerst sizeof(d->cwd)
	if (return_ptr == NULL)
	{
		ft_printf("bash: pwd: %s\n", strerror(errno));
		return ((int**)1);
	}
	// if (d->cwd == NULL)
	// 	return (0);
	printf("OUT: d->cwd: \t%s\n", d->cwd);
	i = ft_strlen(d->cwd);
	printf("I:\t[%i]\n", i);
	free(check->list);
	check->list = malloc(sizeof(char*) * (i + 1));
	//PROTECTION
	ft_strlcpy(check->list, d->cwd, i + 1);
	check->echo = check->list; //MOET check->list HIERNA NIET GEFREED WORDEN?
	printf("check->echo:\t%s\n", check->echo);
	printf("check->list:\t%s\n", check->list);
	// free(check);
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
