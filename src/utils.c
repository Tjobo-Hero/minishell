/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 15:55:01 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/09/30 16:53:32 by rbraaksm      ########   odam.nl         */
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

void	create_delete_new(t_new *tmp, int i)
{
	if (i == 0)
	{
		tmp->head = malloc(sizeof(char*) * PATH_MAX);
		tmp->echo = malloc(sizeof(char*) * PATH_MAX);
		tmp->list = malloc(sizeof(char*) * PATH_MAX);
		tmp->tmp = malloc(sizeof(char*) * PATH_MAX);
		ft_bzero(tmp->head, sizeof(PATH_MAX));
		ft_bzero(tmp->echo, sizeof(PATH_MAX));
		ft_bzero(tmp->list, sizeof(PATH_MAX));
		ft_bzero(tmp->tmp, sizeof(PATH_MAX));
	}
	else
	{
		free(tmp->head);
		free(tmp->echo);
		free(tmp->list);
		free(tmp->tmp);
	}
}

void	clear_new(t_new *new)
{
	clear_str(new->list);
	clear_str(new->head);
	clear_str(new->echo);
	clear_str(new->tmp);
}

char	*create_str(int size)
{
	char	*tmp;

	tmp = malloc(sizeof(char*) * size + 1);
	ft_bzero(tmp, size);
	return (tmp);
}