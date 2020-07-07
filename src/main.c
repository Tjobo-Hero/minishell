/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/07/07 09:25:19 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_home_path(t_mini *d)
{
	int i;
	char *temp;

	i = 0;
	while (d->env[i] && ft_strncmp(d->env[i], "HOME=", 5) != 0)
		i++;
	if (d->env[i] == NULL)
		return ;
	temp = ft_substr(d->env[i], 5, ft_strlen(d->env[i]) - 4);
	if (temp == NULL)
		return ((void)malloc_error());
	d->home_path = (char*)malloc(sizeof(char*) * (ft_strlen(temp) + 3));
	/* bij fout free temp */
	if (!d->home_path)
		return ((void)malloc_error());
	i = 0;
	while (temp[i])
	{
		d->home_path[i] = temp[i];
		i++;
	}
	d->home_path[i] = '/';
	d->home_path[i + 1] = '\0';
	free(temp);
}

void	init_env(t_mini *d)
{
	extern char **environ;
	int i;

	i = 0;
	d->c_env = 0;
	while (environ[d->c_env] != NULL)
		d->c_env++;
	d->env = (char **)malloc(sizeof(char*) * (d->c_env + 1));
	if (!d->env)
		return ((void)malloc_error());
	while (environ[i] != NULL)
	{
		(d->env)[i] = (char*)malloc(sizeof(char*) * (ft_strlen(environ[i])));
		if (!(d->env)[i])
			return ((void)malloc_error());
		ft_strlcpy((d->env)[i], environ[i], (ft_strlen(environ[i]) + 1));
		i++;
	}
	(d->env)[i] = NULL;
	get_home_path(d);
}

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
	if (d->singleq || d->doubleq)
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
		if (str[i] == c && (str[i - 1] != '\\' && str[i - 1] != c) && d->set == 0)
			count++;
		if ((str[i] == '\'' || str[i] == '\"') && str[i - 1] != '\\')
			set_on_off(d, str[i]);
		i++;
	}
	if (str[i - 1] == c)
		count--;
	return (count);
}

void	*ft_memalloc(size_t size)
{
	void *temp;

	temp = malloc(size);
	if (temp <= 0)
		return (NULL);
	ft_bzero(temp, size);
	return (temp);
}

char	*commands(t_mini *d, char *str, int *x, char c)
{
	char *tmp;
	int	i;

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
	i++;
	tmp = malloc(sizeof(char*) * (i - *x));
	if (tmp == NULL)
		return (NULL);
	ft_strlcpy(tmp, &str[*x], (i - *x));
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
		if (d->args == NULL)
			exit(1);
		a = 0;
		x = 0;
		while (a < d->c_arg)
		{
			while (d->cmd[i][x] == 32)
				x++;
			d->args[a] = commands(d, d->cmd[i], &x, ' ');
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
	d->cmd = ft_memalloc(sizeof(char*)* (d->c_cmd));
	if (d->cmd == NULL)
		exit(1);
	while (i < d->c_cmd)
	{
		while (d->line[x] == ';')
			x++;
		d->cmd[i] = commands(d, d->line, &x, ';');
		i++;
	}
	split_commands(d);
	ft_free(d, d->cmd, 0);
	free(d->line);
}

int		main(void)
{
	t_mini	d;

	init_env(&d);
	d.exp = NULL;
	d.c_exp = d.c_env;
	screen_clean();
	while (1)
	{
		write(1, "minishell> ", 11);
		if (!(get_next_line(0, &d.line)))
			 return (0);
		get_commands(&d);
	}
	return (0);
}
