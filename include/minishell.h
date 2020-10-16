/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 15:53:15 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/10/16 18:24:28 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../printf/printf.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <stdarg.h>
# include <sys/cdefs.h>

# define ECHO 10
# define COMMAND 7

int	g_ret;

typedef struct		s_pipe
{
	int			fd_in;
	int			fd_out;
	char		*input;
	char		*output;
	int			ispipe[2];
}					t_pipe;

typedef struct		s_env
{
	char			*head;
	char			*list;
	char			*echo;
	int				index;
	int				set;
	int				alpha;
	struct s_env	*next;
}					t_env;

typedef struct		s_cmd
{
	char			*command;
	int				index;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_new
{
	char	*head;
	char	*list;
	char	*echo;
	char	*tmp;
	int		set;
	int		alpha;
}					t_new;

typedef struct		s_arg
{
	int		i;
	int		c_i;
	int		c;
	int		set;
	int		a;
	int		*count;

}					t_arg;

typedef struct	s_mini
{
	char	**split_line;
	char	**environ;
	char	*cwd;
	char	**args;
	char	**orig;
	int		**pipes;
	int		ret;
	int		index;
	int		i;
	int		pids;
	int		forked;
	int		fd;
	int		is_child;
	t_new	new;
	t_env	**echo;
	t_cmd	**commands;
	t_pipe	pipe;
	t_arg	*arg;
}				t_mini;

int		main(void);
int		get_next_line(int fd, char **line);

void	init_env(t_mini *d);
int		new_count_commands(char *str, int *count, char c);
char	**new_fill_commands(t_mini *d, char *str, int *count, int w);
char	**new_fill_commands2(t_mini *d, char *str, int *count);
void	check_arg_and_remove_case(t_mini *d);
void	ft_free(char **args);
void	free_environ(char **environ);

/* commands */
void	command(t_mini *d);
int		**pwd(t_mini *d);
int		**cd(t_mini *d);
int		**export(t_mini *d);
int		**env(t_mini *d);
int		**unset(t_mini *d);
int		**echo(t_mini *d);
int		**exit_own(t_mini *d);
void	check_if_forked(t_mini *d);
void	new_list(t_mini *d);

/* Utils */
t_env	*new_elem(t_mini *d, char *environ);
void	error_malloc(t_mini *d, char **array, char *single, int *count);
int		hash(char *name, int count);
void	push_back(t_env **echo, t_env *new);
t_env	*look_up(char *name, t_env **hash_table);
void	delete_lst(char *name, t_env **hash_table);

void	print_echo(t_env **hash_table);

void	clear_new(t_new *new);
void	create_delete_new(t_mini *d, t_new *tmp, int i);
void	hash_table_insert_index(t_mini *d, t_env *user, t_env **env, int index);
void	set_env(t_env *user, char *environ, int index);
int		**alpha(t_env **env);
t_env	*find_free(t_env **env);
void	init(t_env **tmp, t_cmd **command, int x);
void	init_commands(t_mini *d);

int		check_arg(t_mini *d, t_new *new, char *arg);
void	make_string(t_mini *d, char *arg, char *str);
int		find_lowest(t_env **echo, t_env *new, int cmp);
void	set_alpha(t_env **echo, int cmp);
void	make_echo(t_mini *d, char *echo, char *arg);

int		syntax_check(char *arg);

void	get_commands(t_mini *d, char *line);
int		*count_init(int size);
void	upgrade_line(t_arg *arg, char *in, char *out, int *count);

void	pipes(t_mini *d);
void	redirect(t_mini *d, int n);
char	**new_arg(t_mini *d, char **args, int c, int n);
void	free_int_array(int **arr);
void	remove_case(t_mini *d);
char	*set_elem(char *environ, int i, int len, int type);
int		ft_write(t_mini *d, int fd, char *str);
void	struct_null(t_mini *d);

#endif
