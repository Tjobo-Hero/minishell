/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_run.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:01:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/16 16:17:07 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		**(*start_command(int i))(t_mini *d)
{
	int	**(*command[7])(t_mini *d);

	command[0] = &pwd;
	command[1] = &cd;
	command[2] = &export;
	command[3] = &unset;
	// command[4] = &exit;
	command[5] = &env;
	command[6] = &echo;
	return (command[i]);
}

t_cmd	*look_up_commands(char *name, t_cmd **hash_table)
{
	t_cmd	*tmp;
	int		i;
	int		len;

	i = hash_echo(name, 7);
	len = ft_strlen(name);
	tmp = hash_table[i];
	while (tmp)
	{
		if (!strncmp(name, tmp->head, strlen(tmp->head)) &&
			len == (int)ft_strlen(tmp->head))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

int		**run_commands(t_mini *d)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	check_single_double(d);
	tmp = look_up_commands(d->args[0], d->commands);
	if (tmp == NULL)
		execute(d, d->args);
	else
		d->ret = (int)start_command(tmp->index)(d);
	return (0);
}
