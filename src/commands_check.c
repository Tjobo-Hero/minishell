/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:15:29 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:15:31 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_args_if(t_mini *d, char **array, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0 ||
		ft_strncmp(str, "env", ft_strlen(str)) == 0 ||
		ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
	{
		tmp = array[0];
		array[0] = ft_strdup(str);
		array[0] == NULL ? error_malloc(d, NULL, str, NULL) : 0;
		free(tmp);
	}
	free(str);
}

void		to_lower(t_mini *d, char **array, char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(str);
	tmp == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	while (str[i] != '\0')
	{
		if (ft_tolower(tmp[i]) > 0)
			tmp[i] += 32;
		i++;
	}
	change_args_if(d, array, tmp);
}
