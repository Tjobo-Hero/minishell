/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_export.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 09:53:24 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/08/28 15:18:18 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_first_part(char *arg)
{
	int		i;
	int		slash;

	i = 0;
	// slash = 0;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (arg[i] != '\\' && (arg[i] != 34 || arg[i] != 39 || arg[i] != 95))
			slash = 0;
		else if (arg[i] == '\\')
			slash++;
		else if ((arg[i] == 34 || arg[i] == 39 || arg[i] == 95) && slash % 2 == 1)
			return (0);
		else if (arg[i] < 65 || (arg[i] > 90 && arg[i] < 95) || (arg[i] < 97 && arg[i] > 122))
			return (0);
		if (slash > 1)
			return (0);
		i++;
	}
	return (1);
	// int i;
	// int s;
	// int dou;
	// int slash;

	// i = 0;
	// s = 1;
	// dou = 1;
	// while (arg[i] != '=' && arg[i] != '\0')
	// {
	// 	if (arg[i] != '\\')
	// 		slash = 0;
	// 	else if (arg[i] == '\\')
	// 		slash++;
	// 	if ((arg[i] == '\'' || arg[i] == '`') && slash % 2 == 1 && dou != -1)
	// 		s *= -1;
	// 	else if (arg[i] == '\"' && slash % 2 == 1 && s != -1)
	// 		dou *= -1;
	// 	i++;
	// }
	// if (dou == -1 || s == -1 || arg[i - 1] == '\\')
	// 	return (0);
	// if (slash > 1)
	// 	return (0);
	// return (1);
}

// int		check_for_quotes(char *arg)
// {
// 	int i;
// 	int s;
// 	int dou;
// 	int slash;

// 	i = 0;
// 	s = 1;
// 	dou = 1;
// 	while (arg[i] != '\0')
// 	{
// 		if (arg[i] != '\\' && arg[i - 1] != '\\')
// 			slash = 0;
// 		else if (arg[i] == '\\')
// 			slash++;
// 		if (arg[i] == '\'' && slash % 2 == 0 && dou != -1)
// 			s *= -1;
// 		else if (arg[i] == '\"' && slash % 2 == 0 && s != -1)
// 			dou *= -1;
// 		i++;
// 	}
// 	if (dou == -1 || s == -1 || arg[i - 1] == '\\')
// 		return (0);
// 	return (1);
// }

int		check_for_quotes(char *arg)
{
	int i;
	int s;
	int dou;
	int slash;

	i = 0;
	s = 1;
	dou = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] != '\\' && arg[i - 1] != '\\')
			slash = 0;
		else if (arg[i] == '\\')
			slash++;
		if ((arg[i] == '\'' || arg[i] == '`') && slash % 2 == 0 && dou != -1)
			s *= -1;
		else if (arg[i] == '\"' && slash % 2 == 0 && s != -1)
			dou *= -1;
		i++;
	}
	if (dou == -1 || s == -1 || arg[i - 1] == '\\')
		return (0);
	return (1);
}

void	fill_str(char *str, char c, int *i, int *slash)
{
	str[*i] = c;
	*i = *i + 1;
	*slash = 0;
}

void	make_string(char *arg, char *str)
{
	int		i;
	int		c;
	int		slash;

	i = 0;
	c = 0;
	while (arg[i] != '\0')
	{
		if ((arg[i] > 64 && arg[i] < 91) || arg[i] == 95 || (arg[i] > 96 && arg[i] < 123))
			fill_str(str, arg[i], &c, &slash);
		else if (arg[i] == '=')
			fill_str(str, arg[i], &c, &slash);
		else if (arg[i] == '\\' && slash % 2 == 1)
			fill_str(str, arg[i], &c, &slash);
		// else if ((arg[i] == '\'' || arg[i] == '`' || arg[i] == '\"') && slash % 2 == 1)
		// 	fill_str(str, arg[i], &c, &slash);
		i++;
	}
}

char	*check_arg(t_mini *d, char *arg)
{
	char	str[PATH_MAX];
	char	*tmp;
	int		i;
	int		x;

	i = 0;
	x = 0;
	(void)d;
	clear_str(str);
	printf("----- EXPORT -----\n");
	printf("First check: ");
	if (check_for_quotes(arg) == 0)
		return (NULL);
	printf("passed\n");
	printf("Second check: ");
	if (check_first_part(arg) == 0)
		return (NULL);
	printf("passed\n");
	make_string(arg, str);
	// while (arg[i] != '\0')
	// {
	// 	if (arg[i] == '\'' && arg[i - 1] != '\\')
	// 		fill(str, arg, &i, &x);
	// 	else if (arg[i] == '\"' && arg[i - 1] != '\\')
	// 		fill(str, arg, &i, &x);
	// 	else
	// 	{
	// 		str[x] = arg[i];
	// 		x++;
	// 		i++;
	// 	}
	// }
	// printf("string: %s\n", str);
	// tmp = str;
	printf("String: %s\n", str);
	tmp = str;
	clear_str(str);
	return (tmp);
}