/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 15:55:01 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/07/09 17:33:16 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		screen_clean(void)
{
	write(1, "\e[1;1H\e[2J", 11);
}

int			malloc_error(void)
{
	ft_printf("malloc fail env_copy");
	exit(1);
	return (0);
}

char		**char_malloc_error(void)
{
	ft_printf("malloc fail env_copy");
	exit(1);
	return (0);
}

void	clear_str(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = '\0';
		i++;
	}
}
