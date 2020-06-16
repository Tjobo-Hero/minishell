/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pointer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/09 11:41:41 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/08 12:23:25 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_pointer_prec(t_flags *flags, long nbr, int len, int count)
{
	while (flags->prec > len)
	{
		count += write(1, "0", 1);
		flags->prec--;
	}
	count += ft_putnbr(nbr, len, flags);
	return (count);
}

int		ft_pointer_min_plus(t_flags *flags, long nbr, int len, int count)
{
	count += ft_putstring(flags->str);
	flags->width = flags->width - (flags->prec < len ? len : flags->prec) -
	ft_strlen(flags->str);
	if (flags->dot == 1)
		count = ft_pointer_prec(flags, nbr, len, count);
	if (flags->dot == 0)
		count += ft_putnbr(nbr, len, flags);
	while (flags->width > 0)
	{
		count += write(1, flags->zero == 0 ? " " : "0", 1);
		flags->width--;
	}
	return (count);
}

int		ft_pointer_min_zero(t_flags *flags, long nbr, int len, int count)
{
	if (flags->width == 0)
	{
		count += ft_putstring(flags->str);
		flags->str = "";
	}
	if (flags->prec == 0 && nbr == 0 && flags->width == 0)
		return (count);
	flags->width = flags->width - (flags->prec < len ? len : flags->prec) -
	ft_strlen(flags->str);
	while (flags->width > 0)
	{
		count += write(1, flags->zero == 0 ? " " : "0", 1);
		flags->width--;
	}
	if (flags->str)
		count += ft_putstring(flags->str);
	if (flags->dot == 1)
		return (ft_pointer_prec(flags, nbr, len, count));
	count += ft_putnbr(nbr, len, flags);
	return (count);
}

int		ft_pointer_basic(t_flags *flags, long nbr, int len, int count)
{
	if (flags->dot == 0)
		count += ft_putstring(flags->str);
	count += ft_putnbr(nbr, len, flags);
	return (count);
}

int		ft_pointer(va_list args, t_flags *flags)
{
	unsigned long	nbr;
	int				len;
	int				count;

	nbr = va_arg(args, unsigned long);
	count = 0;
	len = ft_number_length(nbr, 16);
	if (flags->width == 0 && flags->dot == 0)
		return (ft_pointer_basic(flags, nbr, len, count));
	else if (flags->min == 1)
		return (ft_pointer_min_plus(flags, nbr, len, count));
	else
		return (ft_pointer_min_zero(flags, nbr, len, count));
}
