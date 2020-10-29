/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_init.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:16:34 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:16:35 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while ((line[start] == ' ' || line[start] == ';') && c != 0)
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

char		**line_split(t_mini *d, char *str, int *count, char c)
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
	free(count);
	return (tmp);
}
