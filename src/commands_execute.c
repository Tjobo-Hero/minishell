/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_execute.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 17:41:41 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/06 11:56:08 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_str(t_env *tmp, int *i, int *c, int *x)
{
	char	*str;

	str = ft_strdup((const char*)tmp->list);
	str == NULL ? char_malloc_error() : 0;
	*i = 0;
	*c = *c + 1;
	*x = *x + 1;
	return (str);
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
	d->environ = ft_memalloc(sizeof(char *) * (d->index + 1));
	d->environ == NULL ? void_malloc_error() : 0;
	while (i < ECHO)
	{
		if (d->echo[i])
		{
			tmp = d->echo[i];
			while (tmp && tmp->index != c)
				tmp = tmp->next;
		}
		if (tmp != NULL && tmp->index == c)
			d->environ[x] = make_str(tmp, &i, &c, &x);
		else
			i++;
	}
	d->environ[c] = NULL;
}

void		close_ifnot_and_dup(t_mini *d)
{
	int i;

	i = 0;
	while (d->pipes[i])
	{
		if (d->pipes[i][0] > 2 && d->pipes[i][0] != d->pipe.fd_in)
			close(d->pipes[i][0]);
		if (d->pipes[i][1] > 2 && d->pipes[i][1] != d->pipe.fd_out)
			close(d->pipes[i][1]);
		i++;
	}
	if (d->pipe.fd_in > 0 && dup2(d->pipe.fd_in, 0) < 0)
		exit(1);
	if (d->pipe.fd_out > 0 && dup2(d->pipe.fd_out, 1) < 0)
		exit(1);
}

static char	*update_path(char *cmd, char *path)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strtrim(path, ":");
	tmp2 = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = ft_strjoin(tmp2, cmd);
	free(tmp2);
	return (tmp);
}

static void	get_path(t_mini *d, char **abspath)
{
	t_env		*path;
	struct stat	statstruct;
	char		**new;
	char		*tmp;
	int			i;
	int			*count;

	path = look_up("PATH", d->echo);
	if (path == NULL)
		return ;
	count = count_init(PATH_MAX);
	i = new_count_commands(path->list, count, ':');
	new = new_fill_commands(path->list, count, i);
	i = 0;
	while (new[i])
	{
		tmp = update_path(d->args[0], new[i]);
		if (stat(tmp, &statstruct) != -1)
		{
			*abspath = tmp;
			return ;
		}
		free(tmp);
		i++;
	}
	ft_free(new);
	(void)abspath;
}

static void	execute(t_mini *d, char **cmd)
{
	char		*tmp;
	struct stat	statstruct;
	char		*abspath;

	abspath = NULL;
	close_ifnot_and_dup(d);
	get_path(d, &abspath);
	make_environ(d);
	tmp = ft_strjoin("/bin/", cmd[0]);
	if (!abspath && d->args[0][0] != '.' && stat(d->args[0], &statstruct) <= 0)
		printf("bash: %s: command not found\n", d->args[0]);
	else if (!abspath && execve(d->args[0], d->args, d->environ) == -1)
		printf("bash: %s: %s\n", d->args[0], strerror(errno));
	else if (abspath && execve(d->args[0], d->args, d->environ) == -1)
		printf("bash: %s: %s\n", d->args[0], strerror(errno));
	d->is_child = 0;
	ft_free(d->environ);
	free(tmp);
	exit(127);
}

void	check_if_forked(t_mini *d)
{
	if (d->forked)
		execute(d, d->args);
	else
	{
		if (fork() == 0)
			execute(d, d->args);
		else
			d->pids++;
	}
}
