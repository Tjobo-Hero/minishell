/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/24 17:17:46 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char **cmd)
{
	int i;
	extern char **environ;

	i = 0;
	printf("%s\n", environ[0]);
	printf("%s\n", environ[1]);
	printf("%s\n", environ[2]);
	printf("%s\n", environ[3]);
	if (fork() == 0)
	{
		execve(cmd[0], cmd, NULL);
		exit(0);
	}
	wait(&i);
}

void	cmd_env(char **env)
{
	int i_env;

	i_env = 0;
	printf("\x1b[32mSTART\x1b[0m\n");
	while (env[i_env] != NULL)
	{
		ft_printf("%s\n", env[i_env]);
		i_env++;
	}
}

void	init_env(t_mini *d)
{
	extern char **environ;
	int i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	d->env = (char **)malloc(sizeof(char*) * i + 1);
	if (!d->env)
	{
		ft_printf("malloc fail struct");
		exit(1);
	}
	i = 0;
	while (environ[i] != NULL)
	{
		(d->env)[i] = (char*)malloc(sizeof(char*) * ft_strlen(environ[i]));
		if (!(d->env)[i])
		{
			ft_printf("malloc fail struct");
			exit(1);
		}
		ft_strlcpy((d->env)[i], environ[i], ft_strlen(environ[i]));
		i++;
	}
	(d->env)[i] = NULL;
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

void	set_env(t_mini *d)
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

	i = 0;
	while (i < d->c_cmd)
	{
		getcwd(d->cwd, sizeof(d->cwd));
		set_env(d);
		d->args = ft_split(d->cmd[i], ' ');
		if (d->args[0] == NULL)
			return ;
		if (ft_strncmp(d->args[0], "pwd", ft_strlen(d->args[0])) == 0)
			ft_printf("%s\n", getcwd(d->cwd, sizeof(d->cwd)));
		else if (ft_strncmp(d->args[0], "cd", ft_strlen(d->args[0])) == 0)
			cd(d);
		else if (ft_strncmp(d->args[0], "env", ft_strlen(d->args[0])) == 0)
			cmd_env(d->env);
		ft_free(d->args, d->cmd[i], ' ');
		i++;
	}
}

int		count_commands(char *cmd, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] != c && (cmd[i + 1] == c || cmd[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int		main(void)
{
	t_mini	d;

	init_env(&d);
	while (1)
	{
		write(1, "minishell> ", 11);
		if (!(get_next_line(0, &d.line)))
			 return (0);
		d.cmd = ft_split(d.line, ';');
		d.c_cmd = count_commands(d.line, ';');
		run_commands(&d);
		ft_free(d.cmd, d.line, ';');
		free(d.line);
	}
	return (0);
}