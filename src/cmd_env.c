/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_env.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:03:42 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/06/25 10:04:02 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_env(char **env)
{
	int i_env;

	i_env = 0;
	printf("\x1b[32mSTART\x1b[0m\n");
	while (env[i_env] != NULL)
	{
		ft_printf("%s\n", env[i_env]);
		i_env++;
	}
}