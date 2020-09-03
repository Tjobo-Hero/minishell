/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export_utils2.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 19:50:17 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/03 13:21:00 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		fill_str(char *str, char c, int i)
{
	str[i] = c;
	return (1);
}

int		fill_single_quote(t_mini *d, char *arg, char *str, int c)
{
	int	i;

	i = c;
	d->i++;
	while (arg[d->i] != '\0')
	{
		if (arg[d->i] == '\\' || arg[d->i] == '\"')
		{
			str[i] = '\\';
			i++;
		}
		if (arg[d->i + 1] == '\0' && arg[d->i] == '\'')
			break ;
		str[i] = arg[d->i];
		i++;
		d->i++;
	}
	return (i);
}

int		fill_double_quote(t_mini *d, char *arg, char *str, int c)
{
	int	slash;
	int	i;

	d->i++;
	i = c;
	slash = 0;
	while (arg[d->i] != '\0')
	{
		if (arg[d->i] != '\\' && arg[d->i - 1] != '\\')
			slash = 0;
		else if (arg[d->i] == '\\')
			slash++;
		if (arg[d->i] == '\\' && slash % 2 == 1)
		{
			str[i] = '\\';
			i++;
			d->i++;
		}
		if (arg[d->i + 1] == '\0' && arg[d->i] == '\"')
			break ;
		i += fill_str(str, arg[d->i], i);
		d->i++;
	}
	return (i);
}

void	make_string(t_mini *d, char *arg, char *str)
{
	int		c;
	int		slash;

	d->i = 0;
	c = 0;
	slash = 0;
	while (d->i < (int)ft_strlen(arg))
	{
		if (arg[d->i] != '\\' && arg[d->i - 1] != '\\')
			slash = 0;
		else if (arg[d->i] == '\\')
			slash++;
		if (arg[d->i] == '\'' && slash % 2 == 0)
			c = fill_single_quote(d, arg, str, c);
		else if (arg[d->i] == '\"' && slash % 2 == 0)
			c = fill_double_quote(d, arg, str, c);
		else if (arg[d->i] == '\\' && slash == 1 && arg[d->i + 1] != '\\')
			d->i++;
		else
		{
			c += fill_str(str, arg[d->i], c);
			d->i++;
		}
	}
}
