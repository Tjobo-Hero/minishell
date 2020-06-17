/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_n.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/09 11:41:41 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/08 12:53:02 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_flag_n(va_list args, t_flags *flags, int count)
{
	intmax_t	nbr;

	if (flags->hh == 1)
		nbr = (signed char)va_arg(args, int *);
	else if (flags->h == 1)
		nbr = (short)va_arg(args, int *);
	else if (flags->l)
		nbr = *va_arg(args, long *);
	else if (flags->ll)
		nbr = *va_arg(args, long long *);
	else
		nbr = va_arg(args, int);
	nbr = count;
	return (nbr);
}
