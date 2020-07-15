/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:01:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/15 14:57:22 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_environ(char **environ)
{
	int		i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	while (i > 0)
	{
		free(environ[i - 1]);
		i--;
	}
	free(environ);
}

void		make_environ(t_mini *d)
{
	int		i;

	i = 0;
	// while (d->env[i] != NULL)
	// 	i++;
	// d->environ = ft_memalloc(sizeof(char *) * (i + 1));
	// // if (d->environ == NULL)
	// // 	return (NULL);
	// i = 0;
	// while (d->env[i] != NULL)
	// {
	// 	d->environ[i] = ft_strdup((const char*)d->env[i]->list);
	// 	i++;
	// }
	d->environ[i] = NULL;
}

void		execute(t_mini *d, char **cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin("/bin/", cmd[0]);
	make_environ(d);
	if (fork() == 0)
	{
		if (execve(tmp, cmd, d->environ) == -1)
			ft_printf("bash: %s: command not found\n", d->args[0]);
		exit(0);
	}
	wait(&i);
	free_environ(d->environ);
	free(tmp);
}

char	*find_command(int i)
{
	char	*command[6];

	command[0] = "pwd";
	command[1] = "cd";
	command[2] = "export";
	command[3] = "env";
	command[4] = "unset";
	// command[15] = "exit";
	// command[18] = "echo";
	command[5] = NULL;
	return (command[i]);
}

int		**(*start_command(int i))(t_mini *d)
{
	int	**(*command[5])(t_mini *d);

	command[0] = &pwd;
	command[1] = &cd;
	command[2] = &export;
	command[3] = &env;
	command[4] = &unset;
	return (command[i]);
}

char		*to_lower(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(str);
	while (str[i] != '\0')
	{
		if (ft_tolower(tmp[i]) > 0)
			tmp[i] += 32;
		i++;
	}
	return (tmp);
}

void	check_single_double(t_mini *d)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = ft_strlen(d->args[0]);
	if ((d->args[0][len - 1] == '\'' && d->args[0][len - 2] == '\'') ||
		(d->args[0][len - 1] == '\"' && d->args[0][len - 2] == '\"'))
	{
		tmp = d->args[0];
		d->args[0] = malloc(sizeof(char *) * (len - 1));
		ft_strlcpy(d->args[0], tmp, len - 1);
		free(tmp);
	}
}

void	change_args_if(t_mini *d, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0 ||
		ft_strncmp(str, "env", ft_strlen(str)) == 0 ||
		ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
	{
		tmp = d->args[0];
		d->args[0] = ft_strdup(str);
		free(tmp);
	}
	free(str);
}

int		**run_commands(t_mini *d)
{
	char	*tmp;
	int		i;
	int		len;

	tmp = NULL;
	i = 0;
	check_single_double(d);
	tmp = to_lower(d->args[0]);
	if (tmp)
		change_args_if(d, tmp);
	len = ft_strlen(d->args[0]);
	while (i < 5)
	{
		if (!ft_strncmp(d->args[0], find_command(i), len))
		{
			d->ret = (int)start_command(i)(d);
			return (0);
		}
		i++;
	}
	execute(d, d->args);
	return (0);
}
