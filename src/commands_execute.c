/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_execute.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:16:09 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:16:11 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_ifnot_and_dup(t_mini *d)
{
	int i;
	int	check;

	i = 0;
	check = 0;
	while (d->pipes[i])
	{
		if (d->pipes[i][0] > 2 && d->pipes[i][0] != d->pipe.fd_in)
			check = close(d->pipes[i][0]);
		if (d->pipes[i][1] > 2 && d->pipes[i][1] != d->pipe.fd_out)
			check = close(d->pipes[i][1]);
		if (check == -1)
			error_malloc(d, NULL, NULL, NULL);
		i++;
	}
	if (d->pipe.fd_in > 0 && dup2(d->pipe.fd_in, 0) < 0)
		exit(1);
	if (d->pipe.fd_out > 0 && dup2(d->pipe.fd_out, 1) < 0)
		exit(1);
}

static char	*update_path(t_mini *d, char *cmd, char *path)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strtrim(path, ":");
	tmp == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	tmp2 = ft_strjoin(tmp, "/");
	tmp2 == NULL ? error_malloc(d, NULL, tmp, NULL) : 0;
	free(tmp);
	tmp = ft_strjoin(tmp2, cmd);
	tmp == NULL ? error_malloc(d, NULL, tmp2, NULL) : 0;
	free(tmp2);
	return (tmp);
}

static char	*get_path(t_mini *d, struct stat *statstruct, t_env *path)
{
	char		**new;
	int			*count;
	char		*tmp;
	int			i;

	i = 0;
	count = ft_calloc(PATH_MAX, sizeof(int*));
	count == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	new = line_split(d, path->list, count, ':');
	while (new[i])
	{
		tmp = update_path(d, d->args[0], new[i]);
		if (stat(tmp, statstruct) != -1)
		{
			ft_free(new);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	ft_free(new);
	return (NULL);
}

void		execute(t_mini *d)
{
	struct stat	statstruct;
	char		*abspath;
	t_env		*path;

	close_ifnot_and_dup(d);
	abspath = NULL;
	path = look_up("PATH", d->echo);
	if (path != NULL)
		abspath = get_path(d, &statstruct, path);
	make_environ(d);
	if (!abspath && d->args[0][0] != '.' && d->args[0][0] != '/'
			&& stat(d->args[0], &statstruct) < 0)
		print_error("bash: ", d->args[0], ": command not found", NULL);
	else if (!abspath && execve(d->args[0], d->args, d->environ) == -1)
		print_error("bash: ", d->args[0], " ", strerror(errno));
	else if (abspath && execve(abspath, d->args, d->environ) == -1)
		print_error("bash: ", d->args[0], " ", strerror(errno));
	d->is_child = 0;
	ft_free(d->environ);
	exit(127);
}
