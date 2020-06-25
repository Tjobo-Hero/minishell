/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:01:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/06/25 16:21:55 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char **cmd)
{
	int i;
	// extern char **environ;

	i = 0;
	// printf("%s\n", environ[0]);
	// printf("%s\n", environ[1]);
	// printf("%s\n", environ[2]);
	// printf("%s\n", environ[3]);
	if (fork() == 0)
	{
		execve(cmd[0], cmd, NULL);
		exit(0);
	}
	wait(&i);
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
}

void	update_env(t_mini *d)
{
	int		i;

	i = 0;
	while (d->env[i])
	{
		if (!ft_strncmp(d->env[i], "PWD", 3) && d->env[i][3] == '=')
			break ;
		i++;
	}
	// clear_str(d->env[i]);
	// ft_strlcat(d->env[i], "PWD=", 5);
	// ft_strlcat(d->env[i], d->cwd, ft_strlen(d->cwd) + 5);
}

char    *find_command(int i)
{
    char    *command[3];

    // command[0] = "echo";
    command[0] = "pwd";
    command[1] = "cd";
    // // command[3] = "export";
    // command[4] = "unset";
    // command[5] = "env";
    // command[6] = "exit";
    command[2] = NULL;
    return (command[i]);
}

// char    **(*command(int i))(t_mini *d)
// {
//     char **(*command[3])(t_mini *d);
    
//     // command[0] = &cmd_echo;
//     command[0] = &cd;
//     command[1] = &pwd;
//     // command[3] = "export";
//     // command[4] = "unset";
//     // command[5] = "env";
//     // command[6] = "exit";
//     command[2] = NULL;
//     return (command[i]);
// }

/*
** Builtin commands functions.
*/

char		**(*start_command(int i))(t_mini *d)
{
	char	**(*command[2])(t_mini *d);

	command[0] = &pwd;
	command[1] = &cd;
	// command[2] = &cmd_exit;
	// command[3] = &cmd_env;
	// command[4] = &cmd_setenv;
	// command[5] = &cmd_unsetenv;
	// command[6] = &cmd_help;
	// command[7] = &cmd_pwd;
	// command[8] = &cmd_squirtle;
	return (command[i]);
}

char	**run_commands(t_mini *d)
{
	int		c;
    int     i;

    c = 0;
	i = 0;
    ft_printf("%d\n", d->c_cmd);
	while (c < d->c_cmd)
	{
		getcwd(d->cwd, sizeof(d->cwd));
		update_env(d);
		d->args = ft_split(d->cmd[c], ' ');
        d->c_arg = count_commands(d->cmd[c], ' ');
		if (d->args[0] == NULL)
			return (NULL);
        while (i < 2)
        {
		    if (!ft_strncmp(d->args[0], find_command(i), ft_strlen(d->args[0])))
                    start_command(i)(d);
            i++;
        }
		ft_free(d, d->args, 1);
		c++;
	}
    return (NULL);
}
