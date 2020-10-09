/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 15:55:01 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/10/02 10:47:26 by rbraaksm      ########   odam.nl         */
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

void	create_delete_new(t_new *tmp, int i)
{
	if (i == 0)
	{
		tmp->head = malloc(sizeof(char*) * PATH_MAX);
		tmp->echo = malloc(sizeof(char*) * PATH_MAX);
		tmp->list = malloc(sizeof(char*) * PATH_MAX);
		tmp->tmp = malloc(sizeof(char*) * PATH_MAX);
	}
	else if (i == 0 || i == 1)
	{
		ft_bzero(tmp->head, sizeof(PATH_MAX));
		ft_bzero(tmp->echo, sizeof(PATH_MAX));
		ft_bzero(tmp->list, sizeof(PATH_MAX));
		ft_bzero(tmp->tmp, sizeof(PATH_MAX));
	}
	else if (i == 3)
	{
		free(tmp->head);
		free(tmp->echo);
		free(tmp->list);
		free(tmp->tmp);
	}
}

char	*create_str(int size)
{
	char	*tmp;

	tmp = malloc(sizeof(char*) * size + 1);
	ft_bzero(tmp, size);
	return (tmp);
}

int	ft_write(int fd, char *str)
{
	int	ret;
	ret = write(fd, str, ft_strlen(str));
	if (ret == -1)
		exit(1);
	return (ret);
}
