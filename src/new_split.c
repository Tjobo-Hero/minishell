// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   new_split.c                                        :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2020/09/10 09:46:11 by rbraaksm      #+#    #+#                 */
// /*   Updated: 2020/09/14 13:33:24 by rbraaksm      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// void	print_tmp(char **tmp)
// {
// 	int	i;

// 	i = 0;
// 	while (tmp[i])
// 	{
// 		printf("tmp[%d]:\t%s\n", i + 1, tmp[i]);
// 		i++;
// 	}
// }

// int		fill_char(t_mini *d, char *out, char *in, int count, char *new)
// {
// 	out[count] = in[d->i];
// 	if ((out[count] != ' ' && out[count] != '|') || d->set == 1)
// 		new[d->c] = out[count];
// 	d->c++;
// 	if (in[d->i] == ' ')
// 	{
// 		while (in[d->i] == ' ')
// 			d->i++;
// 	}
// 	else
// 		d->i++;
// 	d->set = 0;
// 	return (1);
// }

// int		fill_char_quote(t_mini *d, char *out, char *in, int count, char *new)
// {
// 	int		i;
// 	char	c;

// 	i = 1;
// 	c = in[d->i];
// 	// out[count] = in[d->i];
// 	// new[d->c] = out[count];
// 	// count++;
// 	// d->i++;
// 	// d->c++;
// 	count += fill_char(d, out, in, count, new);
// 	while (in[d->i] != c)
// 	{
// 		out[count] = in[d->i];
// 		new[d->c] = out[count];
// 		count++;
// 		d->i++;
// 		d->c++;
// 		i++;
// 	}
// 	count += fill_char(d, out, in, count, new);
// 	// out[count] = in[d->i];
// 	// new[d->c] = out[count];
// 	// count++;
// 	// d->c++;
// 	// d->i++;
// 	return (i + 1);
// }

// int		fill_char_slash(t_mini *d, char *out, char *in, int count, char *new)
// {
// 	int		check;

// 	d->i++;
// 	// if ()
// 	// out[count] = in[d->i];
// 	// new[d->c] = out[count];
// 	if (in[d->i] == '|' || in[d->i] == ' ')
// 		d->set = 1;
// 	check = d->set;
// 	fill_char(d, out, in, count, new);
// 	d->set = check;
// 	// d->i++;
// 	// d->c++;
// 	// d->set *= -1;
// 	return (1);
// 	(void)d;
// 	(void)out;
// 	(void)in;
// 	(void)count;
// 	(void)new;
// }


// void	make_tmp(t_mini *d, char **arg, char *new, int c)
// {
// 	int i;
// 	int	x;

// 	i = 0;
// 	x = c;
// 	while (arg[i])
// 		i++;
// 	arg[i] = malloc(sizeof(char*) * d->c);
// 	ft_strlcpy(arg[i], new, ft_strlen(new) + 1);
// 	// if (ft_strncmp(arg[i], " ", 1) == 0)
// 	// 	free(arg[i]);
// }

// void	make_slash(t_mini *d, char **tmp, char *new, int c)
// {
// 	int i;

// 	i = 0;
// 	make_tmp(d, tmp, new, c);
// 	while (tmp[i])
// 		i++;
// 	tmp[i] = malloc(sizeof(char*) * 2);
// 	tmp[i][0] = '|';
// 	tmp[i][1] = '\0';
// 	(void)d;
// 	(void)new;
// 	(void)c;
// }

// char	**copy_tmp(char **arg, int x)
// {
// 	char	**tmp;
// 	int		i;

// 	i = 0;
// 	while (arg[i])
// 		i++;
// 	tmp = (char**)malloc(sizeof(char*) * (i + x));
// 	i = 0;
// 	while (arg[i])
// 	{
// 		tmp[i] = ft_strdup(arg[i]);
// 		free(arg[i]);
// 		i++;
// 	}
// 	tmp[i] = NULL;
// 	tmp[i + 1] = NULL;
// 	if (x == 3)
// 		tmp[i + 2] = NULL;
// 	free(arg);
// 	return (tmp);
// }

// void	upgrade_line(t_mini *d, char *in, char *out)
// {
// 	char	**tmp;
// 	char	new[PATH_MAX];
// 	int		c;

// 	c = 0;
// 	d->i = 0;
// 	tmp = (char**)malloc(sizeof(char*) * 1);
// 	tmp[0] = NULL;
// 	d->c = 0;
// 	d->set = 0;
// 	clear_str(new);
// 	while (in[d->i] == ' ')
// 		d->i++;
// 	while (in[d->i] != '\0')
// 	{
// 		if (in[d->i] == '\\')
// 			c += fill_char_slash(d, out, in, c, new);
// 		else if (in[d->i] != '\"' && in[d->i] != '\'')
// 			c += fill_char(d, out, in, c, new);
// 		else if (in[d->i] == '\"' || in[d->i] == '\'')
// 			c += fill_char_quote(d, out, in, c, new);
// 		if ((out[c - 1] == ' ' || out[c - 1] == '|' || in[d->i] == '\0') && d->set == 0)
// 		{
// 			tmp = copy_tmp(tmp, out[c - 1] == '|' ? 3 : 2);
// 			printf("NEW:\t%s\n", new);
// 			if ((out[c - 1] == ' ' || in[d->i] == '\0') && out[c - 2] != '|')
// 				make_tmp(d, tmp, new, c);
// 			else if (out[c - 1] == '|')
// 				make_slash(d, tmp, new, c);
// 			clear_str(new);
// 			d->c = 0;
// 			d->set = 0;
// 		}
// 	}
// 	print_tmp(tmp);
// }

// void	new_split(t_mini *d, char *line)
// {
// 	int		x;

// 	clear_str(d->new.nw_tmp);
// 	upgrade_line(d, line, d->new.nw_tmp);
// 	free(line);
// 	x = ft_strlen(d->new.nw_tmp) + 1;
// 	line = malloc(sizeof(char*) * x);
// 	ft_strlcpy(line, d->new.nw_tmp, x);
// 	printf("Line:\t%s\n", line);
// 	// printf("TMP:\t%s\n", d->new.nw_tmp);
// 	// printf("SET:\t%d\n", d->set);
// }