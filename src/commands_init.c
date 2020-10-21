
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/03 10:04:38 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/19 12:02:11 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_set(char *str, char c, int *i)
{
	(*i)++;
	while (str[*i] != c && str[*i] != '\0')
		(*i)++;
}

int		if_same_loop(char *str, int *x, char c)
{
	int	i;

	i = 0;
	while (str[*x] == c)
	{
		(*x)++;
		i++;
	}
	return (i);
}

int		new_count_commands(char *str, int *count, char c)
{
	int	i;
	int x;

	x = 0;
	i = 0;
	while (str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == c && str[i - 1] != '\\')
		{
			count[x] = i;
			while (str[i] == ' ' || str[i] == ';')
				i++;
			if (str[i] == '\0')
				return (x + 1);
			x++;
		}
		if (i > 0 && str[i - 1] != '\\' && (str[i] == '\'' || str[i] == '\"'))
			new_set(str, str[i], &i);
		i++;
	}
	count[x] = i;
	return (x + 1);
}

char	**new_fill_commands(t_mini *d, char *str, int *count, int w)
{
	char	**tmp;
	int		c;
	int		i;
	int		x;

	i = 0;
	c = 0;
	tmp = ft_memalloc(sizeof(char *) * (w + 1));
	tmp == NULL ? error_malloc(d, NULL, str, count) : 0;
	x = count[0];
	while (str[c] == ' ')
		c++;
	while (i < w)
	{
		tmp[i] = ft_memalloc(sizeof(char *) * (x + 1));
		tmp[i] == NULL ? error_malloc(d, tmp, str, count) : 0;
		ft_bzero(tmp[i], (x + 1));
		ft_strlcpy(tmp[i], &str[c], x + 1);
		while (c != count[i])
			c++;
		while ((str[c] == ' ' || str[c] == ';') && str[c] != '\0')
			c++;
		i++;
		x = count[i] - c;
	}
	i = 0;
	return (tmp);
}

static char	**tmp_dup(t_mini *d, char **array, char *line, int *count)
{
	char	**tmp;
	int		i;

	i = 0;
	while (array && array[i])
		i++;
	tmp = (char**)ft_calloc((i + 2), sizeof(char*));
	tmp == NULL ? error_malloc(d, array, line, count) : 0;
	i = 0;
	while (array && array[i])
	{
		tmp[i] = ft_strdup(array[i]);
		if (tmp[i] == NULL)
		{
			ft_free(array);
			error_malloc(d, array, line, count);
		}
		free(array[i]);
		i++;
	}
	tmp[i] = NULL;
	tmp[i + 1] = NULL;
	free(array);
	return (tmp);
}

static int	word(char *line, int *count, int end, char **array)
{
	int		c;
	int		x;
	int		start;

	c = 0;
	x = 0;
	while (count[c] != 0)
		c++;
	count[c] = end;
	while (array[x])
		x++;
	start = (c == 0 ? 0 : count[c - 1]);
	while (line[start] == ' ' || line[start] == ';')
		start++;
	if (start != 0)
	{
		count[c + 1] = end;
		count[c] = start;
	}
	array[x] = ft_calloc((c == 0 ? count[c] : (end - start)), sizeof(char*));
	if (array[x] == NULL)
		return (0);
	ft_strlcpy(array[x], &line[start], ((c == 0 ? count[c] :
	(end - start)) + 1));
	return (1);
}

static void	check_quote(char *line, int *i)
{
	int		set;

	(*i)++;
	if (line[*i - 1] == '\'')
	{
		while (line[*i] != '\'' && line[*i] != '\0')
			(*i)++;
		if (line[*i] == '\'')
			(*i)++;
		return ;
	}
	set = 0;
	while (line[*i] != '\0')
	{
		if (line[*i] == '\\' && set == 0)
			set = set_set(&(*i), 1);
		else
			set = set_set(&(*i), 0);
		if (line[*i] == '\"' && set == 0)
			break ;
	}
	if (line[*i] == '\"')
		(*i)++;
}

static void	check_line(char *line, int *i, int *set)
{
	if (line[*i] == '\\' && (*set) == 0)
		(*set) = set_set(&(*i), 1);
	else if ((line[*i] == '\'' || line[*i] == '\"') && (*set) == 0)
		check_quote(line, &(*i));
	else
		(*set) = set_set(&(*i), 0);
}

char	**line_split(t_mini *d, char *str, int *count, char c)
{
	char	**tmp;
	int		set;
	int		i;

	i = 0;
	set = 0;
	tmp = NULL;
	while (str[i] == ';')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == c && set == 0)
		{
			tmp = tmp_dup(d, tmp, str, count);
			if (!word(str, count, i, tmp))
				error_malloc(d, tmp, str, count);
		}
		check_line(str, &i, &set);
	}
	tmp = tmp_dup(d, tmp, str, count);
	if (!word(str, count, i, tmp))
		error_malloc(d, tmp, str, count);
	return (tmp);
}
