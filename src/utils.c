/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 15:55:01 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/10/16 12:17:00 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_echo(t_env **echo)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	i = 0;
	while (i < ECHO)
	{
		if (echo[i])
			tmp = echo[i];
		while (tmp)
		{
			if (tmp->echo)
				free(tmp->echo);
			if (tmp->list)
				free(tmp->list);
			if (tmp->head)
				free(tmp->head);
			prev = tmp;
			tmp = tmp->next;
			free(prev);
		}
		i++;
	}
	free(echo);
}

void	free_command(t_cmd **commands)
{
	t_cmd	*tmp;
	t_cmd	*prev;
	int		i;

	i = 0;
	while (i < COMMAND)
	{
		if (commands[i])
			tmp = commands[i];
		while (tmp)
		{
			if (tmp->command)
				free(tmp->command);
			prev = tmp;
			tmp = tmp->next;
			free(prev);
		}
		i++;
	}
	free(commands);
}

void	malloc_error_test(t_mini *d, char **array, char *single, int *count)
{
	ft_printf("malloc fail\n");
	if (d->echo)
		free_echo(d->echo);
	if (d->commands)
		free_command(d->commands);
	if (array)
		ft_free(array);
	if (single)
		free(single);
	if (count)
		free(count);
	if (d->arg->count)
		free(d->arg->count);
	if (d->arg)
		free(d->arg);
	if (d->orig)
		ft_free(d->orig);
	if (d->split_line)
		ft_free(d->split_line);
	exit(1);
}

void	malloc_error(void)
{
	ft_printf("malloc fail\n");
	exit(1);
}

void	create_delete_new(t_new *tmp, int i)
{
	if (i == 0)
	{
		tmp->head = ft_calloc(PATH_MAX, sizeof(char*));
		tmp->echo = ft_calloc(PATH_MAX, sizeof(char*));
		tmp->list = ft_calloc(PATH_MAX, sizeof(char*));
		tmp->tmp = ft_calloc(PATH_MAX, sizeof(char*));
		tmp->head == NULL || tmp->echo == NULL || tmp->list == NULL ||
		tmp->tmp == NULL ? malloc_error() : 0;
	}
	else if (i == 1)
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
	if (tmp == NULL)
		exit(1);
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
