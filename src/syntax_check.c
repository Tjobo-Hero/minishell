/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 20:01:49 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/09 10:57:18 by rbraaksm      ########   odam.nl         */
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
		return (-2);
	i++;
	return (i);
}

static int	check_quotes(char *arg, int i)
{
	if (arg[i] == '\"')
		return (check_double(arg, i));
	i++;
	while (arg[i] != '\0' && arg[i] != '\'')
		i++;
	if (arg[i] == '\0')
		return (-2);
	i++;
	return (i);
}

static int	check_redirections(char *arg, int i)
{
	char	*error;
	char	c;

	error = "bash: syntax error near unexpected token `";
	c = arg[i];
	if ((arg[i + 1] == '>' || arg[i + 1] == '<') && arg[i + 1] != c)
	{
		ft_printf("%s%c'\n", error, arg[i + 1]);
		return (-1);
	}
	i++;
	while (arg[i] == ' ')
		i++;
	if (ft_isalnum(arg[i]) == 0)
	{
		if (arg[i] == '/' || arg[i] == '.' || arg[i] == '~')
			return (i);
		if (arg[i] == '\n')
			ft_printf("%snewline'\n", error);
		else
			ft_printf("%s%c'\n", error, arg[i]);
		return (-1);
	}
	return (i);
}

static int	set_set(int *i, int check)
{
	(*i)++;
	return (check == 0 ? 0 : 1);
}

int			syntax_check(char *arg)
{
	int		set;
	int		i;

	set = 0;
	i = 0;
	while (arg[i] == ' ')
		i++;
	if (arg[i] == '|')
		return (ft_printf("bash: syntax error near unexpected token `|'\n"));
	while (arg[i] != '\0')
	{
		if (arg[i] == '\\')
			set = set_set(&i, 1);
		else if ((arg[i] == '\'' || arg[i] == '\"') && set == 0)
			i = check_quotes(arg, i);
		else if ((arg[i] == '>' || arg[i] == '<') && set == 0)
			i = check_redirections(arg, i);
		else
			set = set_set(&i, 0);
		if (i == -1 || i == -2 || (set == 1 && arg[i] == '\n'))
			return (i < 0 ? i : -1);
	}
	return ((set == 0) ? 0 : -2);
}
