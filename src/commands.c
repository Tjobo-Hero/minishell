/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/03 10:04:38 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/08/03 20:14:30 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_set(char *str, char c, int *i)
{
	*i = *i + 1;
	while (str[*i] != c && str[*i] != '\0')
		*i = *i + 1;
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

int	new_count_commands1(char *str, int *count, char c)
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
			if (str[i] != '\0')
				x++;
		}
		if (str[i - 1] != '\\' && (str[i] == '\'' || str[i] == '\"'))
			new_set(str, str[i], &i);
		i++;
	}
	count[x] = i;
	return (x);
}

char	**new_fill_commands1(char *str, int *count, int w, char ch)
{
	char	**tmp;
	int		c;
	int		i;
	int		x;
	int		d;

	i = 0;
	x = 0;
	tmp = ft_memalloc(sizeof(char *) * (w + 1));
		/* protection */
	while (str[x] != '\0')
	{
		d = 0;
		while (str[x] == ch)
		{
			x++;
			d++;
		}
		c = (i == 0 ? count[i] : (count[i] - count[i - 1]));
		tmp[i] = ft_memalloc(sizeof(char *) * (c + 1));
			/* protection */
		c -= d;
		ft_strlcpy(tmp[i], &str[x], c + 1);
		x += c;
		i++;
	}
	return (tmp);
}

void	get_commands(t_mini *d)
{
	int	i;
	int	x;
	int	count_cmd[PATH_MAX];
	int	count_arg[PATH_MAX];

	i = 0;
	d->c_cmd = new_count_commands1(d->line, count_cmd, ';');
	d->cmd = new_fill_commands1(d->line, count_cmd, d->c_cmd, ';');
	while (i < PATH_MAX && count_cmd[i] != 0)
	{
		x = 0;
		d->c_arg = new_count_commands1(d->cmd[i], count_arg, ' ');
		d->args = new_fill_commands1(d->cmd[i], count_arg, d->c_arg, ' ');
		printf("CMD %s\n", d->cmd[i]);
		while (x <= d->c_arg)
		{
			printf("\tARG %s\n", d->args[x]);
			x++;
		}
		i++;
	}
	i = 0;
	printf("--------------------------------------\n\n");
}
