/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_execute.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 17:41:41 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/24 14:49:05 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	fill_char2(t_arg *arg, char c)
{
	arg->c++;
	arg->i++;
	return (c);
}

static void	fill_char_double2(t_arg *arg, char *in, char *out)
{
	char	c;

	c = '\"';
	arg->i++;
			printf("CHAR: %c\n", in[arg->i]);
	while (in[arg->i] != c)
	{
		if (in[arg->i] == '\\' && in[arg->i + 1] != '\"')
			out[arg->c] = fill_char2(arg, in[arg->i]);
		else if (in[arg->i] == '\\' && in[arg->i + 1] == '\"')
		{
			arg->i++;
			out[arg->c] = fill_char2(arg, in[arg->i]);
		}
		else
			out[arg->c] = fill_char2(arg, in[arg->i]);
	}
	arg->i++;
}

static void	fill_char_single2(t_arg *arg, char *in, char *out)
{
	char	c;

	c = in[arg->i];
	arg->i++;
	out[arg->c] = fill_char2(arg, in[arg->i]);
	while (in[arg->i] != c)
		out[arg->c] = fill_char2(arg, in[arg->i]);
	arg->i++;
}

void	upgrade_line2(t_arg *arg, char *in, char *out)
{
	arg->i = 0;
	arg->c = -1;
	arg->set = 0;
	printf("IN: %s\n", in);
	while (in[arg->i] != '\0')
	{
		if (in[arg->i] == '\'')
			fill_char_single2(arg, in, out);
		else if (in[arg->i] == '\"')
			fill_char_double2(arg, in, out);
		else
			out[arg->c] = fill_char2(arg, in[arg->i]);
	}
}

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

static void	execute(t_mini *d, char **cmd)
{
	char	**tmp;
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	tmp = (char**)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (cmd[i])
	{
		clear_str(d->new.tmp);
		upgrade_line2(d->arg, cmd[i], d->new.tmp);
		printf("TMP:\t%s\n", d->new.tmp);
		tmp[i] = ft_strdup(d->new.tmp);
		i++;
	}
	tmp[i] = NULL;
	// i = 0;
	// while (tmp[i])
	// {
	// 	printf("TMP:\t%s\n", tmp[i]);
	// 	i++;
	// }
	// tmp = ft_strjoin("/bin/", cmd[0]);
	// make_environ(d);
	// if (fork() == 0)
	// {
	// 	if (execve(tmp, cmd, d->environ) == -1)
	// 		ft_printf("bash: %s: command not found\n", d->args[0]);
	// 	exit(0);
	// }
	// wait(&i);
	// free_environ(d->environ);
	// free(tmp);
	(void)cmd;
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
