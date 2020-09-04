/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export_utils3.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/04 13:51:04 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/04 16:00:33 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		fill_echo(char *echo, char chr, int c)
{
	echo[c] = chr;
	return (1);
}

int		fill_single(t_mini *d, char *echo, char *arg, int c)
{
	d->i++;
	while (arg[d->i] != '\'')
	{
		echo[c] = arg[d->i];
		d->i++;
		c++;
	}
	d->i++;
	return (c);
}

int		fill_slash2(t_mini *d, char *echo, char *arg, int c)
{
	float	total;
	float	slash;
	int		set;

	slash = 0;
	while (arg[d->i] == '\\')
	{
		slash++;
		d->i++;
	}
	if ((int)slash % 2 == 1 && (arg[d->i] == '\"' || arg[d->i] == '\\'))
		set = 1;
	total = (int)slash % 2 == 1 ? 0.5 + slash / 2 : slash / 2;
	while (total > 0)
	{
		c += fill_echo(echo, '\\', c);
		total--;
	}
	if (set == 1)
	{
		c -= fill_echo(echo, '\0', c - 1);
		c += fill_echo(echo, arg[d->i], c);
		d->i++;
	}
	return (c);
}

int		fill_double(t_mini *d, char *echo, char *arg, int c)
{
	d->i++;
	while (arg[d->i] != '\"')
	{
		if (arg[d->i] == '\\')
			c = fill_slash2(d, echo, arg, c);
		else
		{
			c += fill_echo(echo, arg[d->i], c);
			d->i++;
		}
	}
	d->i++;
	return (c);
}

void	make_echo(t_mini *d, char *echo, char *arg)
{
	int	c;
	int	slash;

	c = 0;
	slash = 0;
	d->i = 0;
	while (arg[d->i] != '=' && arg[d->i] != '\0')
		d->i++;
	d->i++;
	while (arg[d->i] != '\0')
	{
		if (arg[d->i] != '\\' && arg[d->i - 1] != '\\')
			slash = 0;
		else if (arg[d->i] == '\\')
			slash++;
		if (arg[d->i] == '\'' && slash % 2 == 0)
			c = fill_single(d, echo, arg, c);
		else if (arg[d->i] == '\"' && slash % 2 == 0)
			c = fill_double(d, echo, arg, c);
		else
		{
			c += fill_echo(echo, arg[d->i], c);
			d->i++;
		}
	}
}
