/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 17:21:00 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/09 16:32:42 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_args_if(t_mini *d, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0 ||
		ft_strncmp(str, "env", ft_strlen(str)) == 0 ||
		ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
	{
		tmp = d->args[0];
		d->args[0] = ft_strdup(str);
		free(tmp);
	}
	free(str);
}

static void	to_lower(t_mini *d, char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(str);
	if (tmp == NULL)
		return (void_malloc_error());
	while (str[i] != '\0')
	{
		if (ft_tolower(tmp[i]) > 0)
			tmp[i] += 32;
		i++;
	}
	change_args_if(d, tmp);
}

void	check_arg_and_remove_case(t_mini *d)
{
	remove_case(d);
	to_lower(d, d->args[0]);
}
