/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 17:21:00 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/16 18:41:54 by rbraaksm      ########   odam.nl         */
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

char	*to_lower(t_mini *d, char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(str);
	if (tmp == NULL)
		return (*char_malloc_error());
	while (str[i] != '\0')
	{
		if (ft_tolower(tmp[i]) > 0)
			tmp[i] += 32;
		i++;
	}
	change_args_if(d, tmp);
	return (tmp);
}

void	check_single_double(t_mini *d)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = ft_strlen(d->args[0]);
	if ((d->args[0][len - 1] == '\'' && d->args[0][len - 2] == '\'') ||
		(d->args[0][len - 1] == '\"' && d->args[0][len - 2] == '\"'))
	{
		tmp = d->args[0];
		d->args[0] = malloc(sizeof(char *) * (len - 1));
		ft_strlcpy(d->args[0], tmp, len - 1);
		free(tmp);
	}
	to_lower(d, d->args[0]);
}
