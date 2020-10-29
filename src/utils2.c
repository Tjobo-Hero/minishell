/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:14:44 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:14:46 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_dollar(t_mini *d, char *str, int *x)
{
	char	*tmp;

	tmp = ft_calloc((ft_strlen(str)), sizeof(char*));
	tmp == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	if (*x != 0)
		ft_strlcpy(tmp, str, *x + 1);
	ft_strlcpy(&tmp[*x], &str[*x + 1], ft_strlen(&str[*x]) + 1);
	free(str);
	str = ft_strdup(tmp);
	free(tmp);
	(*x) = -1;
	return (str);
}

void	set_on_off(int *doub, int *single, char c)
{
	if (c == '\"' && *single == -1)
		(*doub) *= -1;
	else if (c == '\'' && *doub == -1)
		(*single) *= -1;
}

void	set_array_null(int *single, int *doub, int *y, int *set)
{
	(*single) = -1;
	(*doub) = -1;
	(*y) = 0;
	(*set) = 0;
}

void	print_error(char *error1, char *error2, char *error3, char *error4)
{
	ft_putstr(error1);
	if (error2)
		ft_putstr(error2);
	if (error3)
		ft_putstr(error3);
	if (error4)
		ft_putstr(error4);
	ft_putstr("\n");
}

void	spaces(t_arg *arg, char *in)
{
	while (in[arg->i] == ' ')
		arg->i++;
	arg->i--;
}
