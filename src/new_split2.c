/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_split2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 13:34:29 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/16 14:27:13 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tmp(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		printf("tmp[%d]:\t%s\n", i + 1, tmp[i]);
		i++;
	}
}

char	fill_char(t_mini *d, char *out, char *in, int count)
{
	out[count] = in[d->i];
	return (out[count]);
}

void	fill_char_quote(t_mini *d, char *out, char *in, int count, char *new)
{
	int		check;
	char	c;

	c = in[d->i];
	new[d->c] = fill_char(d, out, in, count);
	d->i++;
	d->c++;
	count++;
	check = 0;
	while (in[d->i] != c && in[d->i] != '\0')
	{
		if (in[d->i] == '\\')
		{
			out[count] = in[d->i];
			new[d->c] = out[count];
			count++;
			d->i++;
			d->c++;
		}
		out[count] = in[d->i];
		new[d->c] = out[count];
		count++;
		d->i++;
		d->c++;
	}
	new[d->c] = fill_char(d, out, in, count);
}

void	fill_char_slash(t_mini *d)
{
	d->i++;
}

void	make_tmp(t_mini *d, char **arg, char *new, int c)
{
	int i;

	i = 0;
	while (arg[i])
		i++;
	arg[i] = malloc(sizeof(char*) * d->c);
	if (c == 0)
		ft_strlcpy(arg[i], new, ft_strlen(new));
	else
		ft_strlcpy(arg[i], new, ft_strlen(new) + 1);
	clear_str(new);
}

void	make_slash(t_mini *d, char **tmp, char *in)
{
	int i;
	int	slash;

	i = 0;
	slash = 0;
	while (tmp[i])
		i++;
	while (in[d->i] == '|')
	{
		d->i++;
		slash++;
	}
	d->i--;
	tmp[i] = malloc(sizeof(char*) * (slash + 1));
	tmp[i][slash] = '\0';
	while (slash > 0)
	{
		tmp[i][slash - 1] = '|';
		slash--;
	}
}

char	**copy_tmp(char **arg, int x)
{
	char	**tmp;
	int		i;

	i = 0;
	while (arg[i])
		i++;
	tmp = (char**)malloc(sizeof(char*) * (i + x));
	i = 0;
	while (arg[i])
	{
		tmp[i] = ft_strdup(arg[i]);
		free(arg[i]);
		i++;
	}
	tmp[i] = NULL;
	tmp[i + 1] = NULL;
	if (x == 3)
		tmp[i + 2] = NULL;
	free(arg);
	return (tmp);
}

char	**upgrade_line(t_mini *d, char *in, char *out)
{
	char	**tmp;
	char	new[PATH_MAX];
	int		c;
	int		set;

	c = 0;
	d->i = 0;
	tmp = (char**)malloc(sizeof(char*) * 1);
	tmp[0] = NULL;
	d->c = 0;
	set = 0;
	clear_str(new);
	while (in[d->i] == ' ')
		d->i++;
	while (in[d->i] != '\0')
	{
		if (in[d->i] == '\\')
		{
			fill_char_slash(d);
			set = 0;
		}
		if ((in[d->i] != '\"' && in[d->i] != '\'') || set == 1)
			new[d->c] = fill_char(d, out, in, c);
		else if (in[d->i] == '\"' || in[d->i] == '\'')
			fill_char_quote(d, out, in, c, new);
		if ((out[c] == ' ') && set == 0)
		{
			tmp = copy_tmp(tmp, 2);
			if (out[c - 1] != '|')
				make_tmp(d, tmp, new, 0);
			d->c = 0;
		}
		else if ((out[c] == '|') && set == 0)
		{
			tmp = copy_tmp(tmp, 3);
			if (out[c - 1] != ' ')
				make_tmp(d, tmp, new, 0);
			make_slash(d, tmp, in);
			d->c = 0;
		}
		else
			d->c++;
		if (in[d->i] == ' ')
			while (in[d->i] == ' ')
				d->i++;
		else
			d->i++;
		c++;
		set = 0;
	}
	if (in[d->i - 1] != ' ')
	{
		tmp = copy_tmp(tmp, 2);
		make_tmp(d, tmp, new, 1);
	}
	return (tmp);
}

void	new_split(t_mini *d, char *line)
{
	int		i;

	i = 0;
	clear_str(d->new.tmp);
	d->tmp_args = upgrade_line(d, line, d->new.tmp);
}
