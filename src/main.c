/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/05 16:15:22 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	split_line(char *line)
{
	char **split_line;
	int i;

	i = 1;
	split_line = ft_split(line, ' ');
	while (split_line[i] != NULL)
	{
		ft_putstr(split_line[i]);
		write(1, "\n", 1);
		i++;
	}
}

void	check_line(char *line)
{
	int i;
	char *echo_str;

	echo_str = "echo";
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == echo_str[i])
			i++;
		if (line[i] == ' ')
			split_line(line);
		i++;
	}
}

int		main(void)
{
	char *line;

	while (1)
	{
		write(1, "minishell> ", 11);
		if (!(get_next_line(0, &line)))
			printf("CHECK");
		check_line(line);
		
	}
	return (0);
}