/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 15:53:15 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/09/16 11:25:34 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include "../libft/libft.h"
# include "../printf/printf.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

# define ENV_SIZE 50
# define ECHO 20
# define STR_MAX 256
# define HEAD_MAX 50

int	g_ret;

typedef struct		s_env
{
	char			head[HEAD_MAX];
	char			list[STR_MAX];
	char			echo[STR_MAX];
	int				index;
	int				set;
	int				alpha;
	struct s_env	*next;
}					t_env;

typedef struct		s_cmd
{
	char			head[6];
	int				index;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_new
{
	char	nw_head[HEAD_MAX];
	char	nw_list[PATH_MAX];
	char	nw_echo[STR_MAX];
	char	nw_tmp[STR_MAX];
	char	nw_set;
}					t_new;

typedef struct	s_mini
{
	int		c;
	char	*line;
	int		set;
	int		i;
	char	**environ;
	char	cwd[PATH_MAX];
	char	**args;
	int		c_arg;
	char	**new_args;
	int		c_pipe;
	int		**pipe;
	int		count_pipe[PATH_MAX];
	int		ret;
	int		index;
	t_new	new;
	t_env	list[ENV_SIZE];
	t_env	*echo[ECHO];
	t_cmd	cmd_list[8];
	t_cmd	*commands[8];
}				t_mini;

int		get_next_line(int fd, char **line);

int		main(void);
void	init_env(t_mini *d);
int		new_count_commands(char *str, int *count, char c);
char	**new_fill_commands(char *str, int *count, int w);
void	check_single_double(t_mini *d);
void	ft_free(char **args);
void	free_environ(char **environ);

/* commands */
int		**run_commands(t_mini *d);
int		**pwd(t_mini *d);
int		**cd(t_mini *d);
int		**export(t_mini *d);
int		**env(t_mini *d);
int		**unset(t_mini *d);
int		**echo(t_mini *d);
void	execute(t_mini *d, char **cmd);
void	new_list(t_mini *d);

/* Utils */
int		int_malloc_error(void);
char	**char_malloc_error(void);
void	void_malloc_error(void);
int		hash_echo(char *name, int count);
t_env	*look_up(char *name, t_env **hash_table);
void	delete_lst(char *name, t_env **hash_table);
void	print_echo(t_env **hash_table);
void	clear_new(t_new *new);
void	clear_str(char *str);
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

void	new_split(t_mini *d, char *line);
void	do_pipes(t_mini *d, int c);
void	count_init(int *count);
#endif
