/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_arg.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/18 12:02:35 by rbraaksm      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/10/12 17:23:17 by tvan-cit      ########   odam.nl         */
=======
/*   Updated: 2020/10/09 17:05:27 by rbraaksm      ########   odam.nl         */
>>>>>>> 7877c706e2e3d0ea0493ee2ab28b78b9018d4f18
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
	// PROTECTION
	while (i < c)
	{
		len = ft_strlen(args[i]);
		new[x] = malloc(sizeof(char*) * (len + 1));
		//PROTECTION
		ft_strlcpy(new[x], args[i], len + 1);
		x++;
		i++;
	}
	new[x] = NULL;
	return (new);
}
