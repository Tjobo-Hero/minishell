/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_fill_flags_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/16 09:17:58 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/08 12:31:07 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_empty_flags(t_flags *flags)
{
	flags->type = ' ';
	flags->min = 0;
	flags->zero = 0;
	flags->dot = 0;
	flags->asterisk = 0;
	flags->width = 0;
	flags->prec = 0;
	flags->hash = 0;
	flags->space = 0;
	flags->plus = 0;
	flags->l = 0;
	flags->ll = 0;
	flags->h = 0;
	flags->hh = 0;
	flags->index = 0;
	flags->neg = 0;
	flags->check = 0;
	flags->str = "";
}

int		ft_flag_type(const char *str, t_flags *flags)
{
	char	*type;
	int		str_i;
	int		type_i;

	type = "cspdiuxX%n";
	str_i = 0;
	while (str[str_i] != '\0')
	{
		type_i = 0;
		while (type[type_i] != '\0')
		{
			if (str[str_i] == type[type_i])
			{
				flags->type = type[type_i];
				return (str_i);
			}
			type_i++;
		}
		str_i++;
	}
	return (0);
}

void	ft_find_width_and_prec(const char *str, t_flags *flags, va_list args)
{
	if (*str == '*' && flags->dot == 0)
		flags->width = va_arg(args, int);
	else if (*str == '*' && flags->dot == 1)
		flags->prec = va_arg(args, int);
	else if (*str >= '0' && *str <= '9' && flags->dot == 0 && flags->width == 0)
		flags->width = ft_atoi(str);
	else if (*str >= '0' && *str <= '9' && flags->dot == 1 && flags->prec == 0)
		flags->prec = ft_atoi(str);
}

void	ft_fill_extra_flags(const char *str, t_flags *flags)
{
	while (*str != flags->type)
	{
		if (*str == 'h' && str[-1] != 'h' && str[+1] != 'h')
			flags->h = 1;
		else if (*str == 'h' && str[-1] == 'h' && str[+1] != 'h')
			flags->hh = 1;
		else if (*str == 'l' && str[-1] != 'l' && str[+1] != 'l')
			flags->l = 1;
		else if (*str == 'l' && str[-1] == 'l' && str[+1] != 'l')
			flags->ll = 1;
		str++;
	}
}

void	ft_fill_flags(const char *str, t_flags *flags, va_list args)
{
	while (*str != flags->type)
	{
		if (*str == '-' && str[-1] != '.')
			flags->min = 1;
		else if (*str == '0' && flags->width == 0 && flags->min == 0)
			flags->zero = 1;
		else if (*str == '.')
			flags->dot = 1;
		else if (*str == '*' || (*str >= '0' && *str <= '9'))
			ft_find_width_and_prec(str, flags, args);
		else if (*str == '#' && (flags->type == 'p' || flags->type == 'x' ||
				flags->type == 'X'))
			flags->hash = 1;
		else if (*str == ' ' && flags->plus == 0)
			flags->space = 1;
		else if (*str == '+')
			flags->plus = 1;
		str++;
	}
}
