/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/17 14:10:19 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	ft_printf("%s\n", cwd);
}

void	check_input(char **cmd)
{	
	if (cmd[0] == NULL)
		return ;
	if (ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0]))== 0)
		pwd();
	else if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0]))== 0)
		cd(cmd);
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

	while (1)
	{
		line = NULL;
		cmd = NULL;
		write(1, "minishell> ", 11);
		if (!(get_next_line(0, &line)))
			 return (0);
		cmd = ft_split(line, ' ');
		check_input(cmd);
		ft_free(line, cmd);
	}
	return (0);
}