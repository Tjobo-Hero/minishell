/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:01:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/02 19:03:59 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char **cmd)
{
	int i;

	i = 0;
	if (fork() == 0)
	{
		execve(cmd[0], cmd, NULL);
		exit(0);
	}
	wait(&i);
}

char    *find_command(int i)
{
    char    *command[5];

    // command[0] = "echo";
    command[0] = "pwd";
    command[1] = "cd";
    command[2] = "export";
    command[3] = "env";
    // command[5] = "env";
    // command[6] = "exit";
    command[4] = NULL;
    return (command[i]);
}

int		**(*start_command(int i))(t_mini *d)
{
	int	**(*command[4])(t_mini *d);

	command[0] = &pwd;
	command[1] = &cd;
	command[2] = &export;
	command[3] = &env;
	// command[3] = &cmd_env;
	// command[4] = &cmd_setenv;
	// command[5] = &cmd_unsetenv;
	// command[7] = &cmd_pwd;
	return (command[i]);
}

int	**run_commands(t_mini *d)
{
	int		c;
    int     i;

    c = 0;
	while (c < d->c_cmd)
	{
		d->args = ft_split(d->cmd[c], ' ');
		if (d->args == NULL)
			exit(1);
        d->c_arg = count_commands(d->cmd[c], ' ');
        i = 0;
        while (i < 4)
        {
		    if (!ft_strncmp(d->args[0], find_command(i), ft_strlen(find_command(i))))
				d->ret = (int)start_command(i)(d);
			i++;
        }
		ft_free(d, d->args, 1);
		c++;
	}
    return (0);
}
