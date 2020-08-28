/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/03 10:04:38 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/08/27 09:42:22 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_set(char *str, char c, int *i)
{
	*i = *i + 1;
	while (str[*i] != c && str[*i] != '\0')
		*i = *i + 1;
}

int		if_same_loop(char *str, int *x, char c)
{
	int	i;

	i = 0;
	while (str[*x] == c)
	{
		*x = *x + 1;
		i++;
	}
	return (i);
}

void	count_init(int *count)
{
	int i;

	i = 0;
	while (count[i] != 0)
	{
		count[i] = 0;
		i++;
	}
}

int		new_count_commands(char *str, int *count, char c)
{
	int	i;
	int x;

	x = 0;
	i = 0;
	count_init(count);
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
		if (str[i - 1] != '\\' && (str[i] == '\'' || str[i] == '\"'))
			new_set(str, str[i], &i);
		i++;
	}
	count[x] = i;
	return (x + 1);
}

char	**new_fill_commands(char *str, int *count, int w)
{
	char	**tmp;
	int		c;
	int		i;
	int		d;

	i = 0;
	c = 0;
	tmp = ft_memalloc(sizeof(char *) * (w + 1));
	tmp == NULL ? char_malloc_error() : 0;
	d = count[0];
	while (i < w)
	{
		tmp[i] = ft_memalloc(sizeof(char *) * (d + 1));
		ft_strlcpy(tmp[i], &str[c], d + 1);
		while (c != count[i])
			c++;
		while (str[c] == ' ' || str[c] == ';')
			c++;
		i++;
		d = count[i] - c;
	}
	return (tmp);
}
