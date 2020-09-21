/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_arg.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/18 12:02:35 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/21 09:20:58 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		length(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' || str[i] == '<')
			break ;
		i++;
	}
	return (i);
}

char	**new_arg(char **args)
{
	char	**new;
	int		len;
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (args[i] && (!ft_strchr(args[i], '>') && !ft_strchr(args[i], '<')))
		i++;
	if (ft_strchr(args[i], '>') || ft_strchr(args[i], '<'))
		i++;
	new = malloc(sizeof(char **) * (i + 1));
	while (x < i)
	{
		len = length(args[x]);
		new[x] = malloc(sizeof(char*) * (len + 1));
		ft_strlcpy(new[x], args[x], len + 1);
		x++;
	}
	new[x] = NULL;
	return (new);
}
