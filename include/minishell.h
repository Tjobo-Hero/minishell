/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 09:32:14 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 13:24:44 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>

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

typedef struct		s_mini
{
	char	**environ;
	char	**args;
	char	**orig;
	int		**pipes;
	char	*cwd;
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
}					t_mini;

int					main(void);
void				init_env(t_mini *d);
char				**line_split(t_mini *d, char *str, int *count, char c);
void				ft_free(char **args);
void				command(t_mini *d);
int					**cmd_pwd(t_mini *d);
int					**cmd_cd(t_mini *d);
int					**cmd_export(t_mini *d);
int					**cmd_env(t_mini *d);
int					**cmd_unset(t_mini *d);
int					**cmd_echo(t_mini *d);
int					**cmd_exit(t_mini *d);
int					hash(char *name, int count);
void				push_back(t_env **echo, t_env *new);
t_env				*look_up(char *name, t_env **hash_table);
void				delete_lst(char *name, t_env **hash_table);
t_env				*new_elem(t_mini *d, char *environ);
void				alpha(t_env **env);
char				*set_elem(char *environ, int i, int len, int type);
int					get_next_line(int fd, char **line);
int					set_set(int *i, int check);
void				commands(t_mini *d, char *line);
int					syntax_check(t_mini *d, char *arg);
void				error_malloc(t_mini *d, char **array, char *single,
					int *count);
void				create_delete_new(t_mini *d, t_new *tmp, int i);
int					check_arg(t_mini *d, t_new *new, char *arg);
void				make_string(t_mini *d, char *arg, char *str);
int					find_lowest(t_env **echo, t_env *new, int cmp);
void				set_alpha(t_env **echo, int cmp);
void				upgrade_line(t_arg *arg, char *in, char *out, int *count);
void				pipes(t_mini *d);
char				**redirect(t_mini *d, int c, int n);
void				return_values(t_mini *d);
void				free_int_array(int **arr);
void				remove_quotes_and_slash(t_mini *d, char **array, char *str);
void				to_lower(t_mini *d, char **array, char *str);
int					ft_write(t_mini *d, char *str);
void				struct_null(t_mini *d);
int					check_quotes(char *arg, int i);
void				execute(t_mini *d);
void				update_array(t_mini *d);
void				set_array_null(int *single, int *doub, int *y, int *set);
void				set_on_off(int *doub, int *single, char c);
char				*remove_dollar(t_mini *d, char *str, int *x);
void				print_error(char *error1, char *error2, char *error3,
					char *error4);
void				make_environ(t_mini *d);
char				*new_orig(char *str, char *tmp, char *find, int i);
#endif
