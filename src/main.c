/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/26 10:58:12 by rbraaksm      ########   odam.nl         */
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
	d->home_path = (char*)malloc(sizeof(char*) * (ft_strlen(temp) + 3));
	if (!d->home_path)
		return ((void)free(temp));
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
	while (environ[i] != NULL)
		i++;
	d->env = (char **)malloc(sizeof(char*) * i + 1);
	if (!d->env)
	{
		ft_printf("malloc fail struct");
		exit(1);
	}
	i = 0;
	while (environ[i] != NULL)
	{
		(d->env)[i] = (char*)malloc(sizeof(char*) * (ft_strlen(environ[i])));
		if (!(d->env)[i])
		{
			ft_printf("malloc fail struct");
			exit(1);
		}
		ft_strlcpy((d->env)[i], environ[i], (ft_strlen(environ[i]) + 1));
		i++;
	}
	(d->env)[i] = NULL;
	get_home_path(d);
}

int		count_commands(char *cmd, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] != c && (cmd[i + 1] == c || cmd[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int		main(void)
{
	t_mini	d;

	init_env(&d);
	screen_clean();
	while (1)
	{
		write(1, "minishell> ", 11);
		if (!(get_next_line(0, &d.line)))
			 return (0);
		d.cmd = ft_split(d.line, ';');
		d.c_cmd = count_commands(d.line, ';');
		run_commands(&d);
		ft_free(&d, d.cmd, 0);
		free(d.line);
		ft_printf("[ret] = %d\n", d.ret);
	}
	return (0);
}
