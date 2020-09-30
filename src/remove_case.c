/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_case.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 11:18:47 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/30 17:49:39 by rbraaksm      ########   odam.nl         */
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
		if (in[arg->i] == '\'')
			fill_char_single(arg, in, out);
		else if (in[arg->i] == '\"')
			fill_char_double(arg, in, out);
		else
			out[arg->c] = fill_char(arg, in[arg->i]);
	}
}

void	remove_case(t_mini *d)
{
	char	*tmp;
	int		i;

	i = 0;
	while (d->args[i])
		i++;
	d->orig = (char**)malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = malloc(sizeof(char*) * PATH_MAX);
	while (d->args[i])
	{
		ft_bzero(tmp, sizeof(PATH_MAX));
		make_line(d->arg, d->args[i], tmp);
		d->orig[i] = ft_strdup(d->args[i]);
		free(d->args[i]);
		d->args[i] = ft_strdup(tmp);
		i++;
	}
	free(tmp);
	d->args[i] = NULL;
	d->orig[i] = NULL;
}
