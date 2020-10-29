/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:20:16 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:20:17 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst1;
	char	*src1;

	dst1 = (char*)dst;
	src1 = (char*)src;
	i = 0;
	if (!dst && !src)
		return (dst);
	while (i < n)
	{
		dst1[i] = src1[i];
		i++;
	}
	return (dst);
}
