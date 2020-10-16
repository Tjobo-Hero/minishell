/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/03 10:04:38 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/16 13:25:49 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_set(char *str, char c, int *i)
{
	(*i)++;
	while (str[*i] != c && str[*i] != '\0')
		(*i)++;
}

int		if_same_loop(char *str, int *x, char c)
{
	int	i;

	i = 0;
	while (str[*x] == c)
	{
		(*x)++;
		i++;
	}
	return (i);
}

int		new_count_commands(char *str, int *count, char c)
{
	int	i;
	int x;

	x = 0;
	i = 0;
	while (str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == c && str[i - 1] != '\\')
		{
			count[x] = i;
			while (str[i] == ' ' || str[i] == ';')
				i++;
			if (str[i] == '\0')
				return (x + 1);
			x++;
		}
		if (i > 0 && str[i - 1] != '\\' && (str[i] == '\'' || str[i] == '\"'))
			new_set(str, str[i], &i);
		i++;
	}
	count[x] = i;
	return (x + 1);
}

char	**new_fill_commands(t_mini *d, char *str, int *count, int w)
{
	char	**tmp;
	int		c;
	int		i;
	int		x;

	i = 0;
	c = 0;
	tmp = ft_memalloc(sizeof(char *) * (w + 1));
	tmp == NULL ? malloc_error_test(d, NULL, str, count) : 0;
	x = count[0];
	while (str[c] == ' ')
		c++;
	while (i < w)
	{
		tmp[i] = ft_memalloc(sizeof(char *) * (x + 1));
		tmp[i] == NULL ? malloc_error_test(d, tmp, str, count) : 0;
		ft_bzero(tmp[i], (x + 1));
		ft_strlcpy(tmp[i], &str[c], x + 1);
		while (c != count[i])
			c++;
		while ((str[c] == ' ' || str[c] == ';') && str[c] != '\0')
			c++;
		i++;
		x = count[i] - c;
	}
	i = 0;
	return (tmp);
}
