/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:03:42 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/06/25 14:55:02 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmd_env(char **env)
{
	int i_env;

	i_env = 0;
	while (env[i_env] != NULL)
	{
		ft_printf("%s\n", env[i_env]);
		i_env++;
	}
	return (0);
}
