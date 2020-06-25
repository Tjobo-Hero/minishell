/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:43:04 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/25 10:22:33 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (1)
	{
		write(1, "minishell> ", 11);
		if (!(get_next_line(0, &d.line)))
			 return (0);
		d.cmd = ft_split(d.line, ';');
		d.c_cmd = count_commands(d.line, ';');
		run_commands(&d);
		ft_free(d.cmd, d.line, ';');
		free(d.line);
	}
	return (0);
}