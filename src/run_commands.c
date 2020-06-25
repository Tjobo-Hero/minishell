/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:01:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/06/25 15:54:01 by tvan-cit      ########   odam.nl         */
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
	clear_str(d->env[i]);
	ft_strlcat(d->env[i], "PWD=", 5);
	ft_strlcat(d->env[i], d->cwd, ft_strlen(d->cwd) + 5);
}

void	run_commands(t_mini *d)
{
	int		i;
	int		fd;

	fd = 1;
	i = 0;
	while (i < d->c_cmd)
	{
		getcwd(d->cwd, sizeof(d->cwd));
		update_env(d);
		d->args = ft_split(d->cmd[i], ' ');
		if (d->args[0] == NULL)
			return ;
		if (ft_strncmp(d->args[0], "pwd", ft_strlen(d->args[0])) == 0)
			d->ret = pwd(d);
		else if (ft_strncmp(d->args[0], "cd", ft_strlen(d->args[0])) == 0)
			d->ret = cd(d);
		else if (ft_strncmp(d->args[0], "env", ft_strlen(d->args[0])) == 0)
			d->ret = cmd_env(d->env);
		// else if (ft_strncmp(d->args[0], "export", ft_strlen(d->args[0])) == 0)
		// 	d->ret = export(d, fd);
		else
			execute(d->args);
		ft_free(d->args, d->cmd[i], ' ');
		i++;
	}
}
