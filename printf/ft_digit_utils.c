/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_digit_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 08:28:22 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/08 12:01:37 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

size_t	ft_number_length(size_t nbr, int base)
{
	unsigned int	len;

	len = 0;
	if (nbr == 0)
		len = 1;
	while (nbr != 0)
	{
		nbr /= base;
		len++;
	}
	return (len);
}

size_t	ft_nbr_long_min(int len)
{
	write(1, "9223372036854775808", 19);
	return (len);
}

size_t	ft_putnbr(size_t nbr, int len, t_flags *flags)
{
	int		i;
	char	buf[16];
	int		base;

	if (nbr == 0)
		return (write(1, "0", 1));
	base = 10;
	if (flags->type == 'x' || flags->type == 'X' || flags->type == 'p')
		base = 16;
	i = len - 1;
	if ((long)nbr == LONG_MIN)
		return (ft_nbr_long_min(len));
	while (nbr != 0)
	{
		if (nbr % base < 10)
			buf[i] = '0' + (nbr % base);
		else if (flags->type == 'x' || flags->type == 'p')
			buf[i] = 87 + (nbr % base);
		else if (flags->type == 'X')
			buf[i] = 55 + (nbr % base);
		nbr /= base;
		i--;
	}
	write(1, buf, len);
	return (len);
}
