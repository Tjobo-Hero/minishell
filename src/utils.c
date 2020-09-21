/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 15:55:01 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/09/21 11:53:50 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		int_malloc_error(void)
{
	ft_printf("malloc fail env_copy");
	exit(1);
	return (0);
}

char	**char_malloc_error(void)
{
	ft_printf("malloc fail env_copy");
	exit(1);
	return (NULL);
}

void	void_malloc_error(void)
{
	ft_printf("malloc fail");
	exit(1);
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
	str[i] = '\0';
}

void	clear_new(t_new *new)
{
	clear_str(new->list);
	clear_str(new->head);
	clear_str(new->echo);
	clear_str(new->tmp);
}