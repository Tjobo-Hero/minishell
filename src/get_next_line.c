/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/15 09:39:12 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/09 18:15:14 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_make_line(char **line, char *buf)
{
	char		*waiting;
	int			lenght;

	lenght = 0;
	waiting = NULL;
	while (buf[lenght] != '\n' || buf[lenght] == '\0')
		lenght++;
	if (buf[lenght] == '\n')
	{
		*line = ft_substr(buf, 0, lenght);
		if (!*line)
		{
			free(buf);
			return (0);
		}
		waiting = buf;
		buf = ft_strdup(&buf[lenght + 1]);
		free(waiting);
		if (!buf)
		{
			free(buf);
			return (0);
		}
	}
	return (buf);
}

char	*ft_making_buf(int const fd, char *bufin, int *ret)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;

	while (*ret > 0)
	{
		*ret = read(fd, buf, BUFFER_SIZE);
		if (*ret < 0)
		{
			free(bufin);
			return (0);
		}
		buf[*ret] = '\0';
		tmp = bufin;
		bufin = ft_strjoin((const char*)bufin, buf);
		free(tmp);
		if (!bufin)
			return (0);
		if (ft_strchr(bufin, '\n'))
			break ;
	}
	return (bufin);
}

int		ft_last_line(char **line, char *buf)
{
	*line = ft_strdup(buf);
	free(buf);
	if (!*line)
		return (-1);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*buf;
	int			ret;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	ret = 1;
	if (!buf)
		buf = ft_strdup("");
	if (!buf)
		return (-1);
	while (ret > 0)
	{
		if ((ft_strchr(buf, '\n')) != NULL)
		{
			buf = ft_make_line(line, buf);
			if (!buf)
				return (-1);
			return (1);
		}
		buf = ft_making_buf(fd, buf, &ret);
		if (!buf)
			return (-1);
	}
	return (ft_last_line(line, buf));
}
