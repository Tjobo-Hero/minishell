/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_case.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 11:18:47 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/23 11:44:23 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	fill_char(t_arg *arg, char c)
{
	arg->c++;
	arg->i++;
	return (c);
}

static void	fill_char_double(t_arg *arg, char *in, char *out)
{
	char	d;
	char	s;

	d = '\"';
	s = '\\';
	arg->i++;
	while (in[arg->i] != '\0')
	{
		if (in[arg->i] == d && in[arg->i + 1] != d)
			break ;
		if (in[arg->i] == s && in[arg->i + 1] != d && in[arg->i + 1] != s)
			out[arg->c] = fill_char(arg, in[arg->i]);
		else if (in[arg->i] == s && (in[arg->i + 1] == d ||
				in[arg->i + 1] == s))
		{
			arg->i++;
			out[arg->c] = fill_char(arg, in[arg->i]);
		}
		else
			out[arg->c] = fill_char(arg, in[arg->i]);
	}
	arg->i++;
}

static void	fill_char_single(t_arg *arg, char *in, char *out)
{
	char	c;

	c = in[arg->i];
	arg->i++;
	out[arg->c] = fill_char(arg, in[arg->i]);
	while (in[arg->i] != c)
		out[arg->c] = fill_char(arg, in[arg->i]);
	arg->i++;
}

static void	make_line(t_arg *arg, char *in, char *out)
{
	arg->i = 0;
	arg->c = -1;
	arg->set = 0;
	while (in[arg->i] != '\0')
	{
		if (in[arg->i] == '\\' && arg->set == 0)
		{
			arg->set = 1;
			arg->i++;
		}
		if (in[arg->i] == '\'' && arg->set == 0)
			fill_char_single(arg, in, out);
		else if (in[arg->i] == '\"' && arg->set == 0)
			fill_char_double(arg, in, out);
		else
		{
			arg->set = 0;
			out[arg->c] = fill_char(arg, in[arg->i]);
		}
	}
}

void		remove_case(t_mini *d, char **array, char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(PATH_MAX, sizeof(char*));
	tmp == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	if (str)
	{
		make_line(d->arg, str, tmp);
		ft_bzero(str, sizeof(PATH_MAX) + 1);
		ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
		free(tmp);
		return ;
	}
	while (array[i])
	{
		ft_bzero(tmp, sizeof(PATH_MAX) + 1);
		make_line(d->arg, array[i], tmp);
		free(array[i]);
		array[i] = ft_strdup(tmp);
		array[i] == NULL ? error_malloc(d, NULL, tmp, NULL) : 0;
		i++;
	}
	free(tmp);
}
