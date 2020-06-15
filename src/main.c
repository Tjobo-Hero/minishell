/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/15 15:30:29 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_input(char **cmd)
{
	char cwd[PATH_MAX];
	
	getcwd(cwd, sizeof(cwd));
	if (ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0]))== 0)
		ft_printf("%s\n", cwd);
}

int		main(void)
{
	char *line;
	char **cmd;

	while (1)
	{
		line = NULL;
		write(1, "minishell> ", 11);
		if (!(get_next_line(0, &line)))
			 return (0);
		cmd = ft_split(line, ' ');
		check_input(cmd);
		free(line);		
	}
	return (0);
}