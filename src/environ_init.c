/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environ_init.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/08 17:02:56 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/16 15:36:33 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			init(t_env **tmp, t_cmd **command, int x)
{
	int	i;

	i = 0;
	if (tmp != NULL)
	{
		while (i < x)
		{
			tmp[i] = NULL;
			i++;
		}
		tmp[i] = NULL;
		return ;
	}
	else
	{
		while (i < x)
		{
			command[i] = NULL;
			i++;
		}
		command[i] = NULL;
	}
}

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

	d->echo = (t_env**)malloc(sizeof(t_env*) * (ECHO + 1));
	d->echo == NULL ? exit(1) : 0;
	d->commands = (t_cmd**)malloc(sizeof(t_cmd*) * (COMMAND + 1));
	if (d->commands == NULL)
	{
		free(echo);
		exit(1);
	}
	init(d->echo, NULL, ECHO);
	init(NULL, d->commands, COMMAND);
	set_env_cmd(d);
	while (environ[d->index] != NULL)
	{
		new = new_elem(d, environ[d->index]);
		push_back(&d->echo[hash(new->head, ECHO)], new);
		d->index++;
	}
	alpha(d->echo);
}
