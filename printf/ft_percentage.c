/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_percentage.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/09 11:41:41 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/07 09:14:43 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_percentage(va_list args, t_flags *flags)
{
	int		count;
	char	character;

	count = 0;
	character = va_arg(args, int);
	if (flags->min == 1)
		count += write(1, "%%", 1);
	while (flags->width > 1)
	{
		count += write(1, flags->zero == 0 ? " " : "0", 1);
		flags->width--;
	}
	if (flags->min == 0)
		count += write(1, "%%", 1);
	return (count);
}
