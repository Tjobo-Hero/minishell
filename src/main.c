/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/18 15:34:54 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_commands(char **cmd, int c_cmd)
{
	char	cwd[PATH_MAX];
	char	**args;
	int		i;

	getcwd(cwd, sizeof(cwd));
	i = 0;
	while (i < c_cmd)
	{
		args = ft_split(cmd[i], ' ');
		if (args[0] == NULL)
			return ;
		if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
			ft_printf("%s\n", cwd);
		else if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
			cd(args, cwd);
		ft_free(args, cmd[i], ' ');
		i++;
	}
}

int		total_commands(char *cmd)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] != ';' && (cmd[i + 1] == ';' || cmd[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int		main(void)
{
	char	*line;
	char	**cmd;
	int		c_cmd;

	while (1)
	{
		line = NULL;
		cmd = NULL;
		write(1, "minishell> ", 11);
		if (!(get_next_line(0, &line)))
			 return (0);
		cmd = ft_split(line, ';');
		c_cmd = total_commands(line);
		run_commands(cmd, c_cmd);
		ft_free(cmd, line, ';');
		free(line);
	}
	return (0);
}