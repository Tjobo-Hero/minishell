/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_split.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/10 09:46:11 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/11 17:54:53 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tmp(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		printf("tmp[%d]:\t%s\n", i + 1, tmp[i]);
		i++;
	}
}

int		fill_char_slash(t_mini *d, char *new, char *line, int count)
{
	d->i++;
	new[count] = line[d->i];
	if (line[d->i] == '|' || line[d->i] == ' ')
		d->set = 1;
	d->i++;
	d->c++;
	return (1);
}

int		fill_char(t_mini *d, char *new, char *line, int count)
{
	new[count] = line[d->i];
	d->c++;
	if (line[d->i] == ' ')
	{
		while (line[d->i] == ' ')
			d->i++;
	}
	else
		d->i++;
	d->set = 0;
	return (1);
}

void	make_tmp(t_mini *d, char **arg, char *new, int *c)
{
	int i;

	i = 0;
	while (arg[i])
		i++;
	arg[i] = malloc(sizeof(char*) * d->c + 1);
	ft_strlcpy(arg[i], &new[*c], d->c + 1);
	*c = d->i - 1;
}

void	make_slash(t_mini *d, char **tmp, char *new, int *c)
{
	int i;

	i = 0;
	while (tmp[i])
		i++;
	tmp[i] = malloc(sizeof(char*) * 2);
	tmp[i][0] = '|';
	tmp[i][1] = '\0';
	(void)d;
	(void)new;
	(void)c;
}

char	**copy_tmp(char **arg, int x)
{
	char	**tmp;
	int		i;

	i = 0;
	while (arg[i])
		i++;
	tmp = (char**)malloc(sizeof(char*) * (i + x));
	i = 0;
	while (arg[i])
	{
		tmp[i] = ft_strdup(arg[i]);
		free(arg[i]);
		i++;
	}
	tmp[i] = NULL;
	tmp[i + 1] = NULL;
	if (x == 3)
		tmp[i + 2] = NULL;
	free(arg);
	return (tmp);
}

void	upgrade_line(t_mini *d, char *line, char *new)
{
	char	**tmp;
	int		x;
	int		c;

	x = 0;
	c = 0;
	d->i = 0;
	tmp = (char**)malloc(sizeof(char*) * 1);
	tmp[0] = NULL;
	d->c = 0;
	while (line[d->i] == ' ')
		d->i++;
	while (line[d->i] != '\0')
	{

		if (line[d->i] != '\\')
			c += fill_char(d, new, line, c);
		else
			c += fill_char_slash(d, new, line, c);
		if (new[c - 1] == ' ' && d->set == 0)
			printf("test\n");
		// if ((line[d->i] == ' ' || line[d->i] == '|' || line[d->i] == '\0') && d->set == 0)
		// {
		// 	while (line[d->i] == ' ')
		// 		d->i++;
		// 	tmp = copy_tmp(tmp, line[d->i] == '|' ? 3 : 2);
		// 	make_tmp(d, tmp, new, &x);
		// 	if (line[d->i] == '|')
		// 		make_slash(d, tmp, new, &x);
		// 	d->c = 0;
		// }
	}
	// print_tmp(tmp);
}

void	new_split(t_mini *d, char *line)
{
	int		x;

	clear_str(d->new.nw_tmp);
	upgrade_line(d, line, d->new.nw_tmp);
	free(line);
	x = ft_strlen(d->new.nw_tmp) + 1;
	line = malloc(sizeof(char*) * x);
	ft_strlcpy(line, d->new.nw_tmp, x);
	printf("Line:\t%s\n", line);
	// printf("TMP:\t%s\n", d->new.nw_tmp);
	// printf("SET:\t%d\n", d->set);
}