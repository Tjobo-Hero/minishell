/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_string_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 16:41:22 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/16 18:40:47 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_putstring(char *s)
{
	int count;

	count = ft_strlen(s);
	if (s != NULL)
		write(1, s, ft_strlen(s));
	return (count);
}
