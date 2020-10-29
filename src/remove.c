/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:13:45 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 11:35:07 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	fill_char(int *c, char x)
{
	(*c)++;
	return (x);
}

static void	fill_double(char *in, char *out, int *i, int *c)
{
	int		set;

	set = 0;
	while (in[*i] != '\0')
	{
		if (in[*i] == '\\' && set == 0)
			set = 1;
		else
			set = 0;
		if (in[*i] == '\"' && set == 0)
			break ;
		if (set && (in[*i + 1] != '\"' && in[*i + 1] != '\\'))
			out[*c] = fill_char(c, in[*i]);
		else if (set && (in[*i + 1] == '\"' || in[*i + 1] == '\\'))
			out[*c] = fill_char(c, in[*i + 1]);
		else if (set == 0 && in[*i] != '\n' && in[*i] != '\\')
			out[*c] = fill_char(c, in[*i]);
		(*i)++;
	}
}

static void	fill_quote(char *in, char *out, int *i, int *c)
{
	(*i)++;
	if (in[*i - 1] == '\'')
	{
		while (in[*i] != '\'')
		{
			if (in[*i] != '\n')
				out[*c] = fill_char(c, in[*i]);
			(*i)++;
		}
	}
	else
		fill_double(in, out, i, c);
}

static void	make_line(char *in, char *out)
{
	int set;
	int i;
	int c;

	set = 0;
	i = 0;
	c = -1;
	while (i < (int)ft_strlen(in) && in[i] != '\0')
	{
		if (in[i] == '\\' && set == 0)
			set = 1;
		else if ((in[i] == '\"' || in[i] == '\'') && set == 0)
			fill_quote(in, out, &i, &c);
		else
		{
			set = 0;
			if (in[i] != '\n')
				out[c] = fill_char(&c, in[i]);
		}
		i++;
	}
}

void		remove_quotes_and_slash(t_mini *d, char **array, char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(PATH_MAX, sizeof(char*));
	tmp == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	if (str)
	{
		make_line(str, tmp);
		ft_bzero(str, sizeof(PATH_MAX));
		ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
		free(tmp);
		return ;
	}
	while (array[i])
	{
		ft_bzero(tmp, sizeof(PATH_MAX));
		make_line(array[i], tmp);
		free(array[i]);
		array[i] = ft_strdup(tmp);
		array[i] == NULL ? error_malloc(d, NULL, tmp, NULL) : 0;
		i++;
	}
	free(tmp);
}
