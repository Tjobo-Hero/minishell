/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hexa_bonus.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 12:32:05 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/08 12:32:09 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_hexa_w_p(t_flags *flags, size_t nbr, int len, int count)
{
	flags->width = flags->width - (flags->prec > len ? flags->prec : len) -
	(flags->hash == 0 ? 0 : 2) - (nbr == 0 && flags->hash == 1 ? -2 : 0);
	if (flags->min == 1)
		count = ft_hexa_prec(flags, nbr, len, count);
	while (flags->width > 0)
	{
		count += write(1, " ", 1);
		flags->width--;
	}
	if (flags->min == 0)
		count = ft_hexa_prec(flags, nbr, len, count);
	return (count);
}

int		ft_hexa_prec(t_flags *flags, size_t nbr, int len, int count)
{
	len = (nbr == 0) ? 0 : len;
	if (flags->hash == 1 && nbr != 0)
		count += ft_putstring(flags->str);
	while (flags->prec > 0 && flags->prec > len)
	{
		count += write(1, "0", 1);
		flags->prec--;
	}
	if (nbr > 0)
		count += ft_putnbr(nbr, len, flags);
	return (count);
}

int		ft_hexa_width(t_flags *flags, size_t nbr, int len, int count)
{
	flags->width = flags->width - len - (flags->hash && nbr != 0 ? 2 : 0);
	if (nbr != 0 && ((flags->hash && flags->zero) || (flags->hash &&
	flags->min)))
		count += ft_putstring(flags->str);
	if (flags->min == 1 && flags->prec == 0)
		count += !flags->dot ? ft_putnbr(nbr, len, flags) : write(1, " ", 1);
	while (flags->width > 0)
	{
		count += write(1, flags->zero == 0 ? " " : "0", 1);
		flags->width--;
	}
	if (flags->min == 0 && flags->hash && !flags->zero && nbr != 0)
		count += ft_putstring(flags->str);
	if (flags->min == 0 && flags->prec == 0)
		count += !flags->dot ? ft_putnbr(nbr, len, flags) : write(1, " ", 1);
	return (count);
}

int		ft_hexa_basic(t_flags *flags, size_t nbr, int len, int count)
{
	if (flags->hash == 1 && nbr != 0)
		count += ft_putstring(flags->str);
	if (flags->dot == 0 || nbr != 0)
		count += ft_putnbr(nbr, len, flags);
	return (count);
}

int		ft_hexa(va_list args, t_flags *flags)
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
	len = ft_number_length(nbr, 16);
	if (flags->width == 0 && flags->prec == 0)
		return (ft_hexa_basic(flags, nbr, len, 0));
	else if (flags->width > 0 && flags->prec == 0)
		return (ft_hexa_width(flags, nbr, len, 0));
	else if (flags->prec >= flags->width)
		return (ft_hexa_prec(flags, nbr, len, 0));
	else
		return (ft_hexa_w_p(flags, nbr, len, 0));
}
