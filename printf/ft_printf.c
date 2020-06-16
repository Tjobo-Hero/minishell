/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 09:55:09 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/08 12:46:40 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_check_flags(t_flags *flags)
{
	if (flags->width < 0)
		flags->min = 1;
	flags->prec = flags->prec * (flags->prec < 0 ? -1 : 1);
	flags->width = flags->width * (flags->width < 0 ? -1 : 1);
	if (flags->plus == 1)
		flags->space = 0;
	if (flags->min == 1)
		flags->zero = 0;
	if (flags->type == 'x' || flags->type == 'p')
		flags->str = "0x";
	if (flags->type == 'X')
		flags->str = "0X";
}

int		ft_print_flags(va_list args, t_flags *flags, int count)
{
	if (flags->type == 'c')
		count += ft_character(args, flags);
	else if (flags->type == 's')
		count += ft_string(args, flags);
	else if (flags->type == 'p')
		count += ft_pointer(args, flags);
	else if (flags->type == 'd' || flags->type == 'i')
		count += ft_digit(args, flags);
	else if (flags->type == 'u')
		count += ft_unsigned(args, flags);
	else if (flags->type == 'x' || flags->type == 'X')
		count += ft_hexa(args, flags);
	else if (flags->type == '%')
		count += ft_percentage(args, flags);
	if (flags->type == 'n')
		count = ft_flag_n(args, flags, count);
	return (count);
}

int		ft_flags(const char *str, va_list args, t_flags *flags, int *index)
{
	int		count;

	count = 0;
	*index += ft_flag_type(str, flags);
	ft_fill_flags(str, flags, args);
	ft_fill_extra_flags(str, flags);
	ft_check_flags(flags);
	count = ft_print_flags(args, flags, count);
	return (count);
}

int		ft_printf(const char *str, ...)
{
	va_list	args;
	t_flags	flags;
	int		count;
	int		i;

	va_start(args, str);
	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		ft_empty_flags(&flags);
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			i++;
			if (str[i] == '%')
				count += write(1, "%%", 1);
			else
				count += ft_flags(&(str[i]), args, &flags, &i);
		}
		else if (str[i] != '%')
			count += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
