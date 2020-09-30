/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 20:01:49 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/25 21:26:57 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_double(char *arg, int i)
{
	int		set;

	set = 0;
	i++;
	while (arg[i] != '\0' && arg[i] != '\"')
	{
		if (set == 1)
			set = 0;
		else if (arg[i] == '\\')
			set = 1;
		i++;
		if (arg[i] == '\"' && set == 1)
			i++;
	}
	if (arg[i] == '\0')
		return (0);
	i++;
	return (i);
}

static int	check_single(char *arg, int i)
{
	if (arg[i] == '\"')
		return (check_double(arg, i));
	i++;
	while (arg[i] != '\0' && arg[i] != '\'')
		i++;
	if (arg[i] == '\0')
		return (0);
	i++;
	return (i);
}

static int	check_syntax(char *arg)
{
	(void)arg;
	return (0);
}

int		check_for_quotes(char *arg)
{
	int i;
	int set;

	i = 0;
	set = 0;
	if (check_syntax(arg))
		return (1);
	while (arg[i] != '\0')
	{
		if (arg[i] == '\\')
		{
			set = 1;
			i++;
		}
		else if ((arg[i] == '\'' || arg[i] == '\"') && set == 0)
			i = check_single(arg, i);
		else
		{
			i++;
			set = 0;
		}
		if (i == 0)
			return (1);
	}
	return ((set == 0) ? 0 : 1);
}
