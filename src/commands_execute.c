/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_execute.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 17:41:41 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/16 18:42:50 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_str(t_env *tmp, int *i, int *c)
{
	char	*str;

	str = ft_strdup((const char*)tmp->list);
	if (str == NULL)
		return (*char_malloc_error());
	*i = 0;
	*c = *c + 1;
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
		{
			d->environ[x] = make_str(tmp, &i, &c);
			x++;
		}
		else
			i++;
	}
	d->environ[c] = NULL;
}

void	execute(t_mini *d, char **cmd)
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
