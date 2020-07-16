/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_commands.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 16:46:22 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/16 21:29:31 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_on_off(t_mini *d, char c)
{
	if (c == '\'' && d->singleq)
		d->singleq = 0;
	else if (c == '\'')
		d->singleq = 1;
	else if (c == '\"' && d->doubleq)
		d->doubleq = 0;
	else if (c == '\"')
		d->doubleq = 1;
	else if (c == '\\' && d->slash)
		d->slash = 0;
	else if (c == '\\')
		d->slash = 1;
	if (d->singleq || d->doubleq || d->slash)
		d->set = 1;
	else
		d->set = 0;
}

int		count(t_mini *d, char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	d->singleq = 0;
	d->doubleq = 0;
	d->set = 0;
	while (str[i] == c && str[i] != '\0')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == c && (str[i - 1] != '\\' && str[i - 1] != c) &&
			d->set == 0)
			count++;
		if ((str[i] == '\'' || str[i] == '\"') && str[i - 1] != '\\')
			set_on_off(d, str[i]);
		i++;
	}
	if (str[i - 1] == c)
		count--;
	return (count);
}

char	*commands(t_mini *d, char *str, int *x, char c)
{
	char	*tmp;
	int		i;

	i = *x;
	d->singleq = 0;
	d->doubleq = 0;
	d->set = 0;
	while (str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == c && d->set == 0 && str[i - 1] != '\\')
			break ;
		if ((str[i] == '\'' || str[i] == '\"') && str[i - 1] != '\\')
			set_on_off(d, str[i]);
		i++;
	}
	tmp = malloc(sizeof(char*) * ((i + 1) - *x));
	if (tmp == NULL)
		return (NULL);
	ft_strlcpy(tmp, &str[*x], ((i + 1) - *x));
	*x = i;
	return (tmp);
}

void	split_commands(t_mini *d)
{
	int	i;
	int	a;
	int	x;

	i = 0;
	while (i < d->c_cmd)
	{
		d->c_arg = count(d, d->cmd[i], ' ');
		d->args = ft_memalloc(sizeof(char*) * (d->c_arg + 1));
		d->args == NULL ? void_malloc_error() : 0;
		a = 0;
		x = 0;
		while (a < d->c_arg)
		{
			while (d->cmd[i][x] == 32)
				x++;
			d->args[a] = commands(d, d->cmd[i], &x, ' ');
			d->args[a] == NULL ? void_malloc_error() : 0;
			a++;
		}
		d->args[d->c_arg] = NULL;
		run_commands(d);
		ft_free(d, d->args, 1);
		i++;
	}
}

void	get_commands(t_mini *d)
{
	int i;
	int x;

	i = 0;
	x = 0;
	d->c_cmd = count(d, d->line, ';');
	d->cmd = ft_memalloc(sizeof(char*) * (d->c_cmd));
	if (d->cmd == NULL)
		return (void_malloc_error());
	if (d->cmd == NULL)
		exit(1);
	while (i < d->c_cmd)
	{
		while (d->line[x] == ';')
			x++;
		d->cmd[i] = commands(d, d->line, &x, ';');
		if (d->cmd[i] == NULL)
			return (void_malloc_error());
		i++;
	}
	split_commands(d);
	ft_free(d, d->cmd, 0);
	free(d->line);
}
