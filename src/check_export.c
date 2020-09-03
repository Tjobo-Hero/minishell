/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_export.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 09:53:24 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/03 09:38:46 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_first_part(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (arg[i] < 65 || (arg[i] > 90 && arg[i] < 95) ||
			(arg[i] < 97 && arg[i] > 122))
			return (0);
		i++;
	}
	return (1);
}

int		check_for_quotes(char *arg)
{
	int i;
	int s;
	int dou;
	int slash;

	i = 0;
	s = 1;
	dou = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] != '\\' && arg[i - 1] != '\\')
			slash = 0;
		else if (arg[i] == '\\' && s == 1)
			slash++;
		if (arg[i] == '\'' && slash % 2 == 0 && dou != -1)
			s *= -1;
		else if (arg[i] == '\"' && slash % 2 == 0 && s != -1)
			dou *= -1;
		i++;
	}
	if (dou == -1 || s == -1 || arg[i - 1] == '\\')
		return (0);
	return (1);
}

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
	while (arg[d->i] != '\'')
	{
		if (arg[d->i] == '\\' || arg[d->i] == '\"')
		{
			str[i] = '\\';
			i++;
		}
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
	while (arg[d->i] != '\0')
	{
		if (arg[d->i] == '\\')
			slash++;
		else
			slash = 0;
		if (slash % 2 == 1)
		{
			str[i] = '\\';
			i++;
			if (arg[d->i + 1] != '\"')
				i += fill_str(str, arg[d->i], i);
		}
		else if (arg[d->i] != '\\')
			i += fill_str(str, arg[d->i], i);
		d->i++;
		if (arg[d->i] == '\"' && slash % 2 == 0)
			break ;
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
		if (arg[d->i] != '\\' && arg[d->i] != '\'' && arg[d->i] != '\"')
			c += fill_str(str, arg[d->i], c);
		else if ((arg[d->i] == '\\' && slash % 2 == 0) || (arg[d->i] == '=') ||
				((arg[d->i] == '\'' || arg[d->i] == '\"') && slash % 2 == 1))
			c += fill_str(str, arg[d->i], c);
		else if (arg[d->i] == '\'' && slash % 2 == 0)
			c = fill_single_quote(d, arg, str, c);
		else if (arg[d->i] == '\"' && slash % 2 == 0)
			c = fill_double_quote(d, arg, str, c);
		d->i++;
	}
}

int		check_arg(t_mini *d, char *arg)
{
	int		i;

	i = 0;
	clear_str(d->nw_list);
	clear_str(d->nw_echo);
	printf("----- EXPORT -----\n");
	printf("Check for quotes: ");
	if (check_for_quotes(arg) == 0)
		return (0);
	printf("passed\n");
	make_string(d, arg, d->nw_list);
	printf("Check first part: ");
	if (check_first_part(d->nw_list) == 0)
		return (0);
	printf("passed\n");
	while (d->nw_list[i] != '=' && d->nw_list[i] != '\0')
		i++;
	if (ft_strchr(d->nw_list, '=') == 0)
		ft_strlcpy(d->nw_echo, d->nw_list, ft_strlen(d->nw_list) + 1);
	else
		ft_strlcpy(d->nw_echo, &d->nw_list[i + 1], (ft_strlen(d->nw_list) - i) + 1);
	ft_strlcpy(d->nw_head, d->nw_list, i + 1);
	return (1);
}
