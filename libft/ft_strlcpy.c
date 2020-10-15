/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 12:23:58 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/07/16 18:36:47 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen((char*)src));
	while (src[i] != '\0' && dstsize - 1 > i)
	{
		dst[i] = src[i];
		i++;
	}
	if (dst[i] != '\0')
		dst[i] = '\0';
	return (ft_strlen(src));
}
