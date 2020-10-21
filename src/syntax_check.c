/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/25 20:01:49 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/21 12:03:56 by rbraaksm      ########   odam.nl         */
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

int			set_set(int *i, int check)
{
	(*i)++;
	return (check == 0 ? 0 : 1);
}

int			syntax_check(t_mini *d, char *arg)
{
	char	*check;
	int		set;
	int		i;

	set = 0;
	i = 0;
	d->arg = (t_arg*)malloc(sizeof(t_arg) * (1));
	d->arg == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	check = ft_strdup(arg);
	check == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	remove_case(d, check);
	while (check[i] == ' ')
		i++;
	if (check[i] == '|' || check[i] == ';')
	{
		ft_printf("bash: syntax error near unexpected token `%c'\n", check[i]);
		return (0);
	}
	while (check[i] != '\0')
	{
		if (check[i] == '\\' && set == 0)
			set = set_set(&i, 1);
		else if ((check[i] == '>' || check[i] == '<') && set == 0)
			i = check_redirections(check, i);
		else
			set = set_set(&i, 0);
		if (i == -1)
			return (0);
	}
	free(check);
	return (1);
}
