/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/15 09:39:12 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/19 14:35:48 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_line(char *line)
{
	int		i;
	int		set;

	i = 0;
	set = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\\' && set == 0)
			set = set_set(&i, 1);
		else if ((line[i] == '\'' || line[i] == '\"') && set == 0)
			i = check_quotes(line, i);
		else
			set = set_set(&i, 0);
		if (i == -2)
		{
			ft_putstr_fd("> ", 1);
			return (0);
		}
	}
	return (1);
}

static int	make_line(char **line, char c)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(*line) + 2));
	if (tmp == NULL)
	{
		free(*line);
		return (-1);
	}
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

int			get_next_line(int fd, char **line)
{
	char	buf[1];
	int		res;

	*line = malloc(sizeof(char *) * 1);
	if (*line == NULL)
		return (-1);
	*line[0] = '\0';
	while (1)
	{
		res = read(fd, buf, 1);
		if (res == -1 || (res == 0 && (*line)[0] == 0))
			return (res);
		if (res != 0)
			res = make_line(line, buf[0]);
		if (res == -1)
			return (res);
		if (buf[0] == '\n')
			if (check_line(*line) == 1)
				return (1);
	}
	return (res);
}
