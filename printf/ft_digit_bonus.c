/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_digit_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/09 11:41:41 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/08 12:30:55 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_calc_width(t_flags *flags, int len, int nbr)
{
	if (nbr == 0 && flags->dot == 1)
		len = 0;
	if (flags->min == 0)
		return (flags->width - (flags->prec > len ? flags->prec : len) -
		(flags->plus || flags->neg || flags->space));
	else
		return (flags->width - (flags->prec > len ? flags->prec : len) -
		(flags->plus || flags->neg || flags->space));
}

int		ft_digit_prec(t_flags *flags, size_t nbr, int len, int count)
{
	len = (nbr == 0) ? 0 : len;
	while (flags->prec > 0 && flags->prec > len)
	{
		count += write(1, "0", 1);
		flags->prec--;
	}
	if (nbr == 0 && (flags->dot && flags->prec == 0))
		return (count);
	count += ft_putnbr(nbr, len, flags);
	return (count);
}

int		ft_digit_minus_plus(t_flags *flags, size_t nbr, int len, int count)
{
	if (flags->plus == 1 || flags->neg)
		count += write(1, flags->neg == 0 ? "+" : "-", 1);
	if (count == 1)
		flags->check = 1;
	if (flags->space == 1 && flags->neg == 0)
		count += write(1, " ", 1);
	flags->width = ft_calc_width(flags, len, nbr);
	count = ft_digit_prec(flags, nbr, len, count);
	while (flags->width > 0)
	{
		count += write(1, " ", 1);
		flags->width--;
	}
	return (count);
}

int		ft_digit_minus_zero(t_flags *flags, size_t nbr, int len, int count)
{
	if ((flags->plus || flags->neg) && !flags->dot && flags->zero)
		count += write(1, flags->neg == 0 ? "+" : "-", 1);
	else if (flags->neg && (flags->width < (len + 1) ||
		flags->width <= flags->prec))
		count += write(1, flags->neg == 0 ? "+" : "-", 1);
	if (count == 1)
		flags->check = 1;
	if (flags->space == 1 && flags->neg == 0)
		count += write(1, " ", 1);
	flags->width = ft_calc_width(flags, len, nbr);
	while (flags->width > 0)
	{
		count += write(1, flags->zero && flags->dot == 0 ? "0" : " ", 1);
		flags->width--;
	}
	if (!flags->check && flags->width <= flags->prec &&
		(flags->plus || flags->neg) && (!flags->zero || flags->dot))
		count += write(1, flags->neg == 0 ? "+" : "-", 1);
	flags->plus = 0;
	flags->space = 0;
	flags->neg = 0;
	count = ft_digit_prec(flags, nbr, len, count);
	return (count);
}

int		ft_digit(va_list args, t_flags *flags)
{
	intmax_t	nbr;
	int			len;

	if (flags->hh == 1)
		nbr = (signed char)va_arg(args, int);
	else if (flags->h == 1)
		nbr = (short)va_arg(args, int);
	else if (flags->l)
		nbr = va_arg(args, long);
	else if (flags->ll)
		nbr = va_arg(args, long long);
	else
		nbr = va_arg(args, int);
	if (nbr < 0)
		flags->neg = 1;
	nbr = nbr * (nbr < 0 ? -1 : 1);
	len = ft_number_length(nbr, 10);
	if (flags->min == 0)
		return (ft_digit_minus_zero(flags, nbr, len, 0));
	else
		return (ft_digit_minus_plus(flags, nbr, len, 0));
}
