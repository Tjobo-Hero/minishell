/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 15:22:38 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/05 14:46:13 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_make_line(char *str, char **line, char *end)
{
	*end = '\0';
	(*line) = ft_strdup(str);
	if ((*line) == NULL)
	{
		free(str);
		return (-1);
	}
	str = ft_memmove(str, (end + 1), (ft_strlen(end + 1) + 1));
	return (1);
}

int		ft_end_of_file(char *str, char **line)
{
	int check;

	check = 0;
	if (str)
		check = ft_make_line(str, line, ft_strchr(str, '\0'));
	free(str);
	if (check == -1)
		return (-1);
	return (0);
}

char	*ft_read_more(char *str, int *ret, int fd)
{
	char	*buf;
	char	*tmp;

	buf = malloc(BUFFER_SIZE + 1);
	if (buf == 0)
	{
		free(str);
		return (0);
	}
	*ret = read(fd, buf, BUFFER_SIZE);
	if (*ret < 0)
	{
		free(buf);
		free(str);
		return (0);
	}
	buf[*ret] = '\0';
	tmp = str;
	str = ft_strjoin(str, buf);
	free(tmp);
	free(buf);
	if (str == 0)
		return (0);
	return (str);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	static char	*str;
	int			check;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (str == NULL)
		str = ft_strdup("");
	if (!str)
		return (-1);
	if (ft_strchr(str, '\n') != NULL)
	{
		check = ft_make_line(str, line, ft_strchr(str, '\n'));
		if (check == -1)
			return (-1);
		return (1);
	}
	else
		str = ft_read_more(str, &ret, fd);
	if (str == 0)
		return (-1);
	if (ret == 0)
		return (ft_end_of_file(str, line));
	return (get_next_line(fd, line));
}
