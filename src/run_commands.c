/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 10:01:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/07 14:20:52 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute(char **cmd)
{
	int i;

	i = 0;
	if (execve(cmd[0], cmd, NULL) == -1)
		i = -1;
	return (i);
}

char    *find_command(int i)
{
    char    *command[6];

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

char	*to_lower(char *str)
{
	char	*tmp;
	int i;

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
		ft_strncmp(str, "env", 3) == 0 ||
		ft_strncmp(str, "pwd", 3) == 0)
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
	if (execute(d->args) == -1)
		ft_printf("bash: %s: command not found\n", d->args[0]);
	return (0);
}
