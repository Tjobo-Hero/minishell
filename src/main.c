/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/16 18:28:35 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (cmd[1] == NULL)
		return ;
	getcwd(cwd, sizeof(cwd));
	if (ft_strncmp("~", cmd[1], ft_strlen(cmd[1])) == 0)
	{
		user = get_user(cwd);
		if (chdir(user))
			perror("");
		free(user);
		return ;
	}
	else if (chdir(cmd[1]))
	{
		ft_printf("bash: %s: %s: ", cmd[0], cmd[1]);
		perror("");
		return ;
	}
	getcwd(cwd, sizeof(cwd));
	ft_printf("NEW: %s\n", cwd);
}

void	pwd(void)
{
	char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	ft_printf("%s\n", cwd);
}

void	check_input(char **cmd)
{
	if (ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0]))== 0)
		pwd();
	else if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0]))== 0)
		cd(cmd);
}

int		count_arguments(char *line)
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
	return (i2);
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

int		main(void)
{
	char	*line;
	char	**cmd;
	int		i;

	i = 0;
	while (1)
	{
		line = NULL;
		write(1, "minishell> ", 11);
		if (!(get_next_line(0, &line)))
			 return (0);
		cmd = ft_split(line, ' ');
		check_input(cmd);
		ft_free(line, cmd);
	}
	return (0);
}