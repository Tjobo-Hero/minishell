/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_unset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 14:55:19 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/09 13:01:10 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	delete_env(t_mini *d, int i)
// {
// 	char	*tmp;

// 	while (d->env[i + 1])
// 	{
// 		tmp = d->env[i];
// 		d->env[i] = d->env[i + 1];
// 		d->env[i + 1] = tmp;
// 		i++;
// 	}
// 	free(d->env[i]);
// 	d->env[i] = NULL;
// 	free(d->env[i + 1]);
// 	d->c_env--;
// }

int		**unset(t_mini *d)
{
// 	int		i;
// 	int		a;
// 	int		len;

// 	a = 1;
// 	len = 0;
// 	while (d->args[a])
// 	{
// 		i = 0;
// 		while (d->env[i])
// 		{
// 			if (ft_strchr(d->args[a], '='))
// 				break ;
// 			len = ft_strlen(d->args[a]);
// 			if (ft_strncmp(d->env[i], d->args[a], len) == 0
// 				&& (d->env[i][len] == '=' || d->env[i][len] == '\0'))
// 			{
// 				delete_env(d, i);
// 				break ;
// 			}
// 			i++;
// 		}
// 		a++;
// 	}
(void)d;
	return (0);
}
