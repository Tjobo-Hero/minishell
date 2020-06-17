/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 15:26:13 by tvan-cit       #+#    #+#                */
/*   Updated: 2019/11/15 11:34:01 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lsrc;
	size_t	ldst;
	size_t	res;

	lsrc = ft_strlen((char*)src);
	ldst = ft_strlen((char*)dst);
	i = 0;
	if (dstsize == 0)
		return (lsrc);
	if (dstsize <= ldst)
		res = (dstsize + lsrc);
	else
		res = lsrc + ldst;
	while (src[i] != '\0' && ldst < (dstsize - 1) && dst != src)
	{
		dst[ldst] = src[i];
		i++;
		ldst++;
	}
	if (ldst < dstsize)
		dst[ldst] = '\0';
	return (res);
}
