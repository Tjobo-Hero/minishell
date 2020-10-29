/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environ.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:13:12 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:13:14 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*new_elem_cmd(t_mini *d, char *command)
{
	t_cmd		*new;
	int			len;

	new = malloc(sizeof(t_cmd));
	new == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	len = ft_strlen(command) + 1;
	new->command = malloc(sizeof(char) * (len + 1));
	new->command == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	ft_strlcpy(new->command, command, len);
	new->index = d->index;
	new->next = NULL;
	return (new);
}

static void		cmd_push_back(t_mini *d, t_cmd **commands, char *command)
{
	t_cmd	*list;

	list = *commands;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new_elem_cmd(d, command);
	}
	else
		*commands = new_elem_cmd(d, command);
}

static void		set_env_cmd(t_mini *d)
{
	char	*command;
	int		index;

	while (d->index < 7)
	{
		d->index == 0 ? command = "pwd" : 0;
		d->index == 1 ? command = "cd" : 0;
		d->index == 2 ? command = "export" : 0;
		d->index == 3 ? command = "unset" : 0;
		d->index == 4 ? command = "exit" : 0;
		d->index == 5 ? command = "env" : 0;
		d->index == 6 ? command = "echo" : 0;
		index = hash(command, COMMAND);
		cmd_push_back(d, &d->commands[index], command);
		d->index++;
	}
	d->index = 0;
}

void			init_env(t_mini *d)
{
	extern char **environ;
	t_env		*new;

	d->echo = (t_env**)ft_calloc((ECHO + 1), sizeof(t_env*));
	d->commands = (t_cmd**)ft_calloc((COMMAND + 1), sizeof(t_cmd*));
	d->echo == NULL ? exit(1) : 0;
	if (d->commands == NULL)
	{
		free(d->echo);
		exit(1);
	}
	set_env_cmd(d);
	while (environ[d->index] != NULL)
	{
		new = new_elem(d, environ[d->index]);
		push_back(&d->echo[hash(new->head, ECHO)], new);
		d->index++;
	}
	alpha(d->echo);
}
