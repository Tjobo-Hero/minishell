/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:20:24 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:20:25 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = (unsigned char*)b;
	i = 0;
	while (i < len)
	{
		tmp[i] = c;
		i++;
	}
	return (b);
}
