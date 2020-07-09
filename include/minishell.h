/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 15:53:15 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/07/09 13:27:24 by rbraaksm      ########   odam.nl         */
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

typedef struct		s_env
{
	char			head[HEAD_MAX];
	char			list[STR_MAX];
	// char			echo[STR_MAX];
	int				set;
	struct s_env	*next;
}					t_env;

typedef struct	s_mini
{
	int		singleq;
	int		doubleq;
	int		set;
	int		exec;
	// char	**env;
	int		c_env;
	char	**exp;
	int		c_exp;
	char	*line;
	char	**cmd;
	int		c_cmd;
	char	cwd[PATH_MAX];
	char	**args;
	int		c_arg;
	int		ret;
	char	*home_path;
	t_env	*env[ENV_SIZE];
	t_env	*echo[ECHO];
	t_env	**export;
}				t_mini;

int		get_next_line(int fd, char **line);

int		main(void);
// void	init_env(t_env **env, t_env **echo);
void	init_env(t_mini *d);
void	ft_free(t_mini *d, char **args, int i);

/* commands */
int		count_commands(char *cmd, char c);
int		**run_commands(t_mini *d);
int		**pwd(t_mini *d);
int		**cd(t_mini *d);
int		**export(t_mini *d);
int		**env(t_mini *d);
int		**unset(t_mini *d);

/* Utils */
void	screen_clean(void);
int		malloc_error(void);
char	**char_malloc_error(void);
unsigned int	hash(char *name);
t_env	*look_up(char *name, t_env **hash_table);

// char	**p_ret(int i, t_mini *d);
#endif
