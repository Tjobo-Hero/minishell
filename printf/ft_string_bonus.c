/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_string_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 15:32:44 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/08 12:33:44 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_string_prec(t_flags *flags, char *str, int len, int count)
{
	int		i;

	i = 0;
	if (flags->min == 1)
	{
		while (str[i] != '\0' && i < flags->prec && flags->prec > 0)
		{
			count += write(1, &str[i], 1);
			i++;
		}
	}
	while ((flags->width - (len > flags->prec ? flags->prec : len)) > 0)
	{
		count += write(1, " ", 1);
		flags->width--;
	}
	if (flags->min == 0)
	{
		while (str[i] != '\0' && i < flags->prec && flags->prec > 0)
		{
			count += write(1, &str[i], 1);
			i++;
		}
	}
	return (count);
}

int		ft_string_width(t_flags *flags, char *str, int len, int count)
{
	int		i;

	i = 0;
	if (flags->min == 1)
		count += write(1, str, len);
	while ((flags->width - len) > 0)
	{
		count += write(1, !flags->min && flags->zero ? "0" : " ", 1);
		flags->width--;
	}
	if (flags->min == 0)
		count += write(1, str, len);
	return (count);
}

int		ft_string(va_list args, t_flags *flags)
{
	int		count;
	int		len;
	char	*str;

	count = 0;
	str = va_arg(args, char*);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen((char *)str);
	if (flags->width == 0 && flags->dot == 0)
	{
		count = write(1, str, len);
		return (count);
	}
	else if (flags->width > 0 && flags->dot == 0)
		count = ft_string_width(flags, str, len, count);
	else
		return (ft_string_prec(flags, str, len, count));
	return (count);
}
