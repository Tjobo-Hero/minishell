/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_character.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 15:32:08 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/16 18:39:43 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_character(va_list args, t_flags *flags)
{
	int		count;
	char	character;

	count = 0;
	character = va_arg(args, int);
	if (flags->min == 1)
		count += write(1, &character, 1);
	while (flags->width > 1)
	{
		count += write(1, flags->zero == 0 ? " " : "0", 1);
		flags->width--;
	}
	if (flags->min == 0)
		count += write(1, &character, 1);
	return (count);
}
