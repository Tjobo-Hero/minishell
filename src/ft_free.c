/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:13:04 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:16:25 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_int_array(int **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	arr = NULL;
}

static void	free_echo(t_env **echo)
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

static void	free_command(t_cmd **commands)
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

static void	error_malloc2(t_mini *d)
{
	if (d->arg->count)
		free(d->arg->count);
	if (d->arg)
		free(d->arg);
	if (d->orig)
		ft_free(d->orig);
	if (d->pipes)
		free_int_array(d->pipes);
	if (d->args)
		ft_free(d->args);
	if (d->environ)
		ft_free(d->environ);
	if (d->new.head)
		free(d->new.head);
	if (d->new.echo)
		free(d->new.echo);
	if (d->new.list)
		free(d->new.list);
	if (d->new.tmp)
		free(d->new.tmp);
}

void		error_malloc(t_mini *d, char **array, char *single, int *count)
{
	ft_putstr_fd(strerror(errno), 1);
	ft_write(d, "\n");
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
	error_malloc2(d);
	exit(1);
}
