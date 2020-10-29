/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:13:58 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:13:59 by rbraaksm      ########   odam.nl         */
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

int			check_quotes(char *arg, int i)
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

static int	error(t_mini *d, char c, int check)
{
	char	*error;

	error = "bash: syntax error near unexpected token `";
	ft_write(d, error);
	if (check == 2)
		ft_write(d, "newline");
	else if (!write(1, &c, 1))
		return (-1);
	if (check == 1)
		if (!write(1, &c, 1))
			return (-1);
	ft_write(d, "\'\n");
	return (-1);
}

static int	check_redirections(t_mini *d, char *arg, int i)
{
	char	c;

	c = arg[i];
	if ((arg[i + 1] == '>' || arg[i + 1] == '<' ||
		arg[i + 1] == ';') && arg[i + 1] != c)
		return (error(d, arg[i + 1], 0));
	if (c == ';' && arg[i + 1] == ';')
		return (error(d, arg[i], 1));
	i++;
	if (arg[i] == c)
		i++;
	while (arg[i] == ' ')
		i++;
	if (ft_isalnum(arg[i]) == 0 && (arg[i] == '\"' &&
		ft_isalnum(arg[i + 1]) == 0))
	{
		if (arg[i] == '/' || arg[i] == '.' || arg[i] == '~')
			return (i);
		if (arg[i] == '\n')
			return (error(d, arg[i], 2));
		else
			return (error(d, arg[i], 0));
	}
	return (i);
}

int			syntax_check(t_mini *d, char *arg)
{
	int		set;
	int		i;

	set = 0;
	i = 0;
	while (arg[i] == ' ')
		i++;
	if (arg[i] == '|' || arg[i] == ';')
		return (error(d, arg[i], 0));
	while (arg[i] != '\0')
	{
		if (arg[i] == '\\' && set == 0)
			set = set_set(&i, 1);
		else if ((arg[i] == '>' || arg[i] == '<' || arg[i] == ';') && set == 0)
			i = check_redirections(d, arg, i);
		else if ((arg[i] == '\'' || arg[i] == '\"') && set == 0)
			i = check_quotes(arg, i);
		else
			set = set_set(&i, 0);
		if (i == -1)
			return (-1);
	}
	return (1);
}
