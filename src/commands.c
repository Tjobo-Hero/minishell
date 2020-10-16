/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/03 10:04:38 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/16 21:28:07 by rbraaksm      ########   odam.nl         */
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
	tmp = (char**)malloc(sizeof(char*) * (i + 2));
	tmp == NULL ? error_malloc(d, array, line, count) : 0;
	i = 0;
	while (array && array[i])
	{
		tmp[i] = ft_strdup(array[i]);
		tmp[i] == NULL ? error_malloc(d, array, line, count) : 0;
		free(array[i]);
		i++;
	}
	tmp[i] = NULL;
	tmp[i + 1] = NULL;
	free(array);
	return (tmp);
}

static char	**word(t_mini *d, char *line, int *count, int i, char **array)
{
	char	**tmp;
	int		c;
	int		x;
	int		len;

	c = 0;
	x = 0;
	tmp = NULL;
	while (count[c] != 0)
		c++;
	count[c] = i - 1;
	tmp = tmp_dup(d, array, line, count);
	while (tmp[x])
		x++;
	len = (c == 0 ? count[c] : count[c] - count[c - 1] - 3);
	tmp[x] = ft_calloc(len + 1, sizeof(char*));
	tmp[x] == NULL ? error_malloc(d, array, line, count) : 0;
	c = (c == 0 ? 0 : count[c - 1] + 1);
	while (line[c] == ' ' || line[c] == ';')
		c++;
	ft_strlcpy(tmp[x], &line[c], len + 2);
	return (tmp);
}

static void	check_quote(char *line, int *i)
{
	int		set;

	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] != '\'' && line[*i] != '\0')
			(*i)++;
		if (line[*i] == '\'')
			(*i)++;
		return ;
	}
	set = 0;
	(*i)++;
	while (line[*i] != '\0')
	{
		if (line[*i] == '\\' && set == 0)
		{
			set = 1;
			(*i)++;
		}
		else
		{
			(*i)++;
			set = 0;
		}
		if (line[*i] == '\"' && set == 0)
			break ;
	}
	if (line[*i] == '\"')
		(*i)++;
}

char	**new_fill_commands2(t_mini *d, char *str, int *count, char c)
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
			tmp = word(d, str, count, i, tmp);
		if (str[i] == '\\')
		{
			set = 1;
			i++;
		}
		else if ((str[i] == '\'' || str[i] == '\"') && set == 0)
			check_quote(str, &i);
		else
		{
			i++;
			set = 0;
		}
	}
	tmp = word(d, str, count, i, tmp);
	return (tmp);
}
