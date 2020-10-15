/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/15 09:39:12 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/15 11:31:06 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		make_line(char **line, char c)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(*line) + 2));
	if (tmp == NULL)
		return (-1);
	while ((*line)[i] != '\0')
	{
		tmp[i] = (*line)[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = '\0';
	free(*line);
	*line = tmp;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char	buf[1];
	int		res;

	*line = malloc(sizeof(char *) * 1);
	if (*line == NULL)
		return (-1);
	*line[0] = '\0';
	res = 1;
	while (res > 0)
	{
		res = read(fd, buf, 1);
		if (buf[0] == '\n' || res == -1 || res == 0)
			return (res);
		res = make_line(line, buf[0]);
	}
	return (res);
}
