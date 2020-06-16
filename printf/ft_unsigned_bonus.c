/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsigned_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 16:11:39 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/08 12:33:57 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_unsigned_w_p(t_flags *flags, size_t nbr, int len, int count)
{
	flags->width = flags->width - (flags->prec > len ? flags->prec : len) -
	(!flags->neg ? 0 : 1) - (flags->plus && !flags->neg ? 1 : 0) -
	(flags->space && flags->min && !flags->neg ? 1 : 0);
	if (flags->min == 1)
		count = ft_unsigned_prec(flags, nbr, len, count);
	while (flags->width > 0)
	{
		count += write(1, " ", 1);
		flags->width--;
	}
	if (flags->min == 0)
	{
		if (flags->plus == 1 || flags->neg == 1)
			count += write(1, flags->neg == 0 ? "+" : "-", 1);
		flags->plus = 0;
		flags->space = 0;
		flags->neg = 0;
		count = ft_unsigned_prec(flags, nbr, len, count);
	}
	return (count);
}

int		ft_unsigned_prec(t_flags *flags, size_t nbr, int len, int count)
{
	if (flags->space == 1 && flags->neg == 0)
		count += write(1, " ", 1);
	if (flags->min == 1 && flags->neg == 1)
		count += write(1, flags->plus && !flags->neg ? "+" : "-", 1);
	else if (flags->neg == 1 || flags->plus == 1)
		count += write(1, flags->neg == 0 ? "+" : "-", 1);
	len = (nbr == 0) ? 0 : len;
	while (flags->prec > 0 && flags->prec > len)
	{
		count += write(1, "0", 1);
		flags->prec--;
	}
	if (nbr > 0)
		count += ft_putnbr(nbr, len, flags);
	return (count);
}

int		ft_unsigned_width(t_flags *flags, size_t nbr, int len, int count)
{
	if ((flags->plus || flags->neg) && (flags->zero || flags->min))
		count += write(1, flags->neg == 0 ? "+" : "-", 1);
	flags->width = flags->width - len - (!flags->space ? 0 : 1) - (flags->neg
	&& !flags->space ? 1 : 0) - (flags->plus && !flags->neg ? 1 : 0);
	if (nbr == 0 && flags->plus == 1 && flags->dot == 1 && flags->min == 0)
		flags->width++;
	if (flags->space == 1 && flags->neg == 0)
		count += write(1, " ", 1);
	if (flags->min == 1 && flags->prec == 0)
		count += !flags->dot ? ft_putnbr(nbr, len, flags) : write(1, " ", 1);
	while (flags->width > 0)
	{
		count += write(1, flags->zero == 0 ? " " : "0", 1);
		flags->width--;
	}
	if ((flags->plus || flags->neg) && (!flags->zero && !flags->min))
		count += write(1, flags->neg == 0 ? "+" : "-", 1);
	if (nbr == 0 && flags->plus == 1 && flags->dot == 1 && flags->min == 0)
		return (count);
	if (flags->min == 0 && flags->prec == 0)
		count += !flags->dot ? ft_putnbr(nbr, len, flags) : write(1, " ", 1);
	return (count);
}

int		ft_unsigned_basic(t_flags *flags, size_t nbr, int len, int count)
{
	if (flags->plus == 1 || flags->neg == 1)
		count += write(1, flags->neg == 0 ? "+" : "-", 1);
	if (flags->space == 1 && flags->neg == 0 && flags->zero == 0)
		count += write(1, " ", 1);
	if (flags->dot == 0 || nbr != 0)
		count += ft_putnbr(nbr, len, flags);
	return (count);
}

int		ft_unsigned(va_list args, t_flags *flags)
{
	size_t	nbr;
	int		len;

	if (flags->hh == 1)
		nbr = (unsigned char)va_arg(args, unsigned int);
	else if (flags->h == 1)
		nbr = (unsigned short)va_arg(args, unsigned int);
	else if (flags->ll == 1)
		nbr = va_arg(args, unsigned long long);
	else if (flags->l)
		nbr = va_arg(args, unsigned long);
	else
		nbr = va_arg(args, unsigned int);
	len = ft_number_length(nbr, 10);
	if (flags->width == 0 && flags->prec == 0)
		return (ft_unsigned_basic(flags, nbr, len, 0));
	else if (flags->width > 0 && flags->prec == 0)
		return (ft_unsigned_width(flags, nbr, len, 0));
	else if (flags->prec >= flags->width)
		return (ft_unsigned_prec(flags, nbr, len, 0));
	else if (flags->width > flags->prec)
		return (ft_unsigned_w_p(flags, nbr, len, 0));
	return (0);
}
