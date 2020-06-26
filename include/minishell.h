/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 15:53:15 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/26 10:44:56 by rbraaksm      ########   odam.nl         */
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

typedef struct	s_mini
{
	char	**env;
	char	*line;
	char	**cmd;
	int		c_cmd;
	char	cwd[PATH_MAX];
	char	**args;
	int		c_arg;
	int		ret;
	char	*home_path;
}				t_mini;

int		get_next_line(int fd, char **line);

int		main(void);
void	ft_free(t_mini *d, char **args, int i);

/* commands */
int		count_commands(char *cmd, char c);
int		**run_commands(t_mini *d);
int		**pwd(t_mini *d);
int		**cd(t_mini *d);
int		cmd_env(char **env);

/* Utils */
void	screen_clean(void);
// char	**p_ret(int i, t_mini *d);
#endif
