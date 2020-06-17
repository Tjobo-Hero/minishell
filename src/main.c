/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/17 17:33:15 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*old_dir(char *cwd)
{
	// char	cwd[PATH_MAX];
	char	*path;
	int		i;
	int		count;

	// getcwd(cwd, sizeof(cwd));
	i = ft_strlen(cwd);
	count = 0;
	while(cwd[i] != '/')
	{
		i--;
		count++;
	}
	count++;
	path = malloc(sizeof(char *) + count);
	ft_strlcpy(path, &cwd[i + 1], count);
	// ft_printf("OLD = %s\n", path);
	return (path);
}

char	*get_user(char *cwd)
{
	char	*user;
	int		i;

	i = 1;
	while (cwd[i] != '/')
		i++;
	i++;
	while (cwd[i] != '/')
		i++;
	i++;
	user = malloc(sizeof(char *) + i);
	ft_strlcpy(user, cwd, i);
	return (user);
}

void	cd(char **cmd)
{
	char	cwd[PATH_MAX];
	char	*user;
	char	*tmp;
	static char	*owd;

	ft_printf("BEGIN OLD: %s\n", owd);
	if (cmd[1] == NULL)
		return ;
	getcwd(cwd, sizeof(cwd));
	if (ft_strncmp("-", cmd[1], ft_strlen(cmd[1])) == 0)
	{
		user = old_dir(owd);
		ft_printf("USER = %s\n", user);
		if (chdir(user))
			perror("");
		free(user);
	}
	tmp = owd;
	owd = ft_strdup(cwd);
	free(tmp);
	if (ft_strncmp("~", cmd[1], ft_strlen(cmd[1])) == 0)
	{
		user = get_user(cwd);
		if (chdir(user))
			perror("");
		free(user);
		return ;
	}
	if (ft_strncmp("-", cmd[1], ft_strlen(cmd[1])) == 0)
	{
		user = old_dir(owd);
		ft_printf("USER = %s\n", user);
		if (chdir(user))
			perror("");
		free(user);
	}
	else if (chdir(cmd[1]))
	{
		ft_printf("bash: %s: %s: ", cmd[0], cmd[1]);
		perror("");
		return ;
	}
	getcwd(cwd, sizeof(cwd));
	ft_printf("END OLD:   %s\n", owd);
	ft_printf("NEW:       %s\n", cwd);
	// free(owd);
	// owd = NULL;
}

void	pwd(void)
{
	char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	ft_printf("%s\n", cwd);
}

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

void	env(t_env *d)
{
	int i_env;

	i_env = 0;
	while (d->env[i_env] != NULL)
	{
		ft_printf("%s\n", d->env[i_env]);
		i_env++;
	}
}

void	check_input(char **cmd, t_env *d)
{
	if (cmd[0] == NULL)
		return ;
	if (ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])) == 0)
		pwd();
	else if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0)
		cd(cmd);
	else if (ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])) == 0)
		env(d);
	else
		execute(cmd);
	// else if (ft_strncmp(cmd[0], "ls", ft_strlen(cmd[0])) == 0)
		// ls(cmd);
}

void	ft_free(char *line, char **cmd)
{
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			i2++;
		i++;
	}
	free(line);
	while (i2 > 0)
	{
		free(cmd[i2 - 1]);
		i2--;
	}
	free(cmd);
}
void	init_env(t_env *d)
{
	extern char **environ;
	int i;
	int i2;

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
	i2 = 0;
	while (environ[i] != NULL)
	{
		d->env[i] = (char*)malloc(sizeof(char*) * ft_strlen(environ[i]));
		if (!d->env[i])
		{
			ft_printf("malloc fail struct");
			exit(1);
		}
		while (environ[i][i2] != '\0')
		{
			d->env[i][i2] = environ[i][i2];
			i2++;
		}
		i2 = 0;
		i++;
	}
	d->env[i] = NULL;
}

static char		*read_the_line(void)
{
	char *line;

	line = NULL;
	get_next_line(0, &line);
	return (line);
}

int		main(void)
{
	char	**commands;
	char	*line;
	t_env	d;

	while (1)
	{
		ft_printf("minishell> ");
		init_env(&d);
		line = read_the_line();
		commands = ft_split(line, ';');
		check_input(commands, &d);
		ft_free(line, commands);
	}
	return (0);
}
