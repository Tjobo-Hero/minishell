/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_run.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:01:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/08/04 23:00:27 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_command(int i)
{
	char	*command[9];

	command[0] = "pwd";
	command[1] = "cd";
	command[2] = "export";
	command[3] = "unset";
	command[4] = "exit";
	command[5] = "env";
	command[6] = "echo";
	command[7] = NULL;
	return (command[i]);
}

int		**(*start_command(int i))(t_mini *d)
{
	int	**(*command[6])(t_mini *d);

	command[0] = &pwd;
	command[1] = &cd;
	command[2] = &export;
	command[3] = &unset;
	// command[4] = &exit;
	command[5] = &env;
	// command[6] = &echo;
	return (command[i]);
}

t_cmd	*look_up_commands(char *name, t_cmd **hash_table, int len)
{
	t_cmd	*tmp;
	int		i;

	i = hash_echo(name, 7);
	tmp = hash_table[i];
	while (tmp != NULL && strncmp(name, tmp->head,  strlen(tmp->head)) != 0 && len == (int)ft_strlen(tmp->head))
		tmp = tmp->next;
	printf("tmp->head\t%s\n", tmp->head);
	return (tmp);
}

int		**run_commands(t_mini *d)
{
	t_cmd	*tmp;
	int		i;
	int		len;

	i = 0;
	check_single_double(d);
	len = ft_strlen(d->args[0]);
	tmp = look_up_commands(d->args[0], d->commands, len);
	if (tmp == NULL)
		execute(d, d->args);
	d->ret = (int)start_command(tmp->index)(d);
	return (0);
	// while (i < 5)
	// {
	// 	if (!ft_strncmp(d->args[0], find_command(i), ft_strlen(find_command(i)))
	// 		&& len == (int)ft_strlen(find_command(i)))
	// 	{
	// 		d->ret = (int)start_command(i)(d);
	// 		return (0);
	// 	}
	// 	i++;
	// }

	// execute(d, d->args);
	// return (0);
}
