/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export_utils2.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:09:40 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:38:55 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_str(t_mini *d, char *str, char c, int i)
{
	str[i] = c;
	d->i++;
	return (1);
}

static int	fill_slash(t_mini *d, char *arg, char *str, int c)
{
	int	neg;
	int	slash;

	slash = 0;
	while (arg[d->i] == '\\')
	{
		c += fill_str(d, str, arg[d->i], c);
		slash++;
	}
	neg = (slash % 2 == 0) ? 0 : 1;
	if (neg == 1)
	{
		if (arg[d->i] != '\"')
		{
			c += fill_str(d, str, '\\', c);
			d->i--;
		}
		else
			c += fill_str(d, str, '\\', c);
	}
	return (c);
}

static int	fill_quote(t_mini *d, char *arg, char *str, int c)
{
	d->i++;
	if (arg[d->i - 1] == '\'')
	{
		while (arg[d->i] != '\'')
		{
			if (arg[d->i] == '\\' || arg[d->i] == '\"')
			{
				str[c] = '\\';
				c++;
			}
			c += fill_str(d, str, arg[d->i], c);
		}
		d->i++;
		return (c);
	}
	while (arg[d->i] != '\"')
	{
		if (arg[d->i] == '\\')
			c = fill_slash(d, arg, str, c);
		else
			c += fill_str(d, str, arg[d->i], c);
	}
	d->i++;
	return (c);
}

void		make_string(t_mini *d, char *arg, char *str)
{
	int		c;
	int		slash;

	d->i = 0;
	c = 0;
	slash = 0;
	while (d->i < (int)ft_strlen(arg))
	{
		if (d->i > 0 && arg[d->i] != '\\' && arg[d->i - 1] != '\\')
			slash = 0;
		else if (arg[d->i] == '\\')
			slash++;
		if (arg[d->i] == '\'' && slash % 2 == 0)
			c = fill_quote(d, arg, str, c);
		else if (arg[d->i] == '\"' && slash % 2 == 0)
			c = fill_quote(d, arg, str, c);
		else if (arg[d->i] == '\\' && slash == 1 && arg[d->i + 1] != '\\')
			d->i++;
		else
			c += fill_str(d, str, arg[d->i], c);
	}
}
