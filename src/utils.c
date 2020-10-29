/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:14:39 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:14:41 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	struct_null(t_mini *d)
{
	d->index = 0;
	d->i = 0;
	d->environ = NULL;
	d->args = NULL;
	d->orig = NULL;
	d->arg = NULL;
	d->pipes = NULL;
	d->new.head = NULL;
	d->new.list = NULL;
	d->new.echo = NULL;
	d->new.tmp = NULL;
	d->is_child = 0;
	d->ret = 0;
}

void	create_delete_new(t_mini *d, t_new *tmp, int i)
{
	if (i == 0)
	{
		tmp->head = ft_calloc(PATH_MAX, sizeof(char*));
		tmp->echo = ft_calloc(PATH_MAX, sizeof(char*));
		tmp->list = ft_calloc(PATH_MAX, sizeof(char*));
		tmp->tmp = ft_calloc(PATH_MAX, sizeof(char*));
		tmp->head == NULL || tmp->echo == NULL || tmp->list == NULL ||
		tmp->tmp == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
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

int		ft_write(t_mini *d, char *str)
{
	int	ret;

	ret = write(d->fd, str, ft_strlen(str));
	if (ret == -1)
		error_malloc(d, NULL, NULL, NULL);
	return (ret);
}

void	ft_free(char **args)
{
	int	x;

	x = 0;
	while (args[x])
	{
		free(args[x]);
		x++;
	}
	free(args);
}
