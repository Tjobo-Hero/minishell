/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_execute.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 17:41:41 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/28 18:13:32 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_str(t_env *tmp, int *i, int *c)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(tmp->head, "=");
	if (tmp1 == NULL)
		return (NULL);
	tmp2 = ft_strjoin(tmp1, tmp->list);
	free(tmp1);
	if (tmp2 == NULL)
		return (NULL);
	(*i) = 0;
	(*c)++;
	return (tmp2);
}

void	make_environ(t_mini *d)
{
	t_env	*tmp;
	int		i;
	int		c;
	int		x;

	i = 0;
	c = 0;
	x = 0;
	d->environ = ft_calloc((d->index + 1), (sizeof(char *)));
	d->environ == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	while (i < ECHO)
	{
		if (d->echo[i])
		{
			tmp = d->echo[i];
			while (tmp && tmp->index != c)
				tmp = tmp->next;
		}
		if (tmp != NULL && tmp->index == c)
		{
			d->environ[x] = make_str(tmp, &i, &c);
			d->environ[x] == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
			x++;
		}
		else
			i++;
	}
	d->environ[c] = NULL;
}

void		close_ifnot_and_dup(t_mini *d)
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

static char	*get_path(t_mini *d, struct stat *statstruct)
{
	t_env		*path;
	char		**new;
	char		*tmp;
	int			i;
	int			*count;

	path = look_up("PATH", d->echo);
	if (path == NULL)
		return (NULL);
	count = ft_calloc(PATH_MAX, sizeof(int*));
	count == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	new = line_split(d, path->list, count, ':');
	i = 0;
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

void	execute(t_mini *d)
{
	struct stat	statstruct;
	char		*abspath;

	close_ifnot_and_dup(d);
	abspath = get_path(d, &statstruct);
	make_environ(d);
	if (abspath && execve(abspath, d->args, d->environ) == -1)
		ft_printf("bash: %s: %s\n", d->args[0], strerror(errno));
	else if (!abspath && d->args[0][0] != '.' && d->args[0][0] != '/'
			&& stat(d->args[0], &statstruct) < 0)
		ft_printf("bash: %s: command not found\n", d->args[0]);
	else if (!abspath && execve(d->args[0], d->args, d->environ) == -1)
		ft_printf("bash: %s: %s\n", d->args[0], strerror(errno));
	d->is_child = 0;
	ft_free(d->environ);
	exit(127);
}

void	check_if_forked(t_mini *d)
{
	if (d->forked)
		execute(d);
	else
	{
		if (fork() == 0)
			execute(d);
		else
			d->pids++;
	}
}
