/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_arg.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/18 12:02:35 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/15 18:27:24 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_arg(char **args, int c, int n)
{
	char	**new;
	int		len;
	int		i;
	int		x;

	x = 0;
	i = c;
	while (args[c] && c < n && (ft_strncmp(args[c], "<", 2) &&
		ft_strncmp(args[c], ">", 2) && ft_strncmp(args[c], ">>", 3)))
		c++;
	new = malloc(sizeof(char **) * ((c - i) + 1));
	new == NULL ? malloc_error() : 0;
	while (i < c)
	{
		len = ft_strlen(args[i]);
		new[x] = malloc(sizeof(char*) * (len + 1));
		new[x] == NULL ? malloc_error() : 0;
		ft_bzero(new[x], len + 1);
		ft_strlcpy(new[x], args[i], len + 1);
		x++;
		i++;
	}
	new[x] = NULL;
	return (new);
}
