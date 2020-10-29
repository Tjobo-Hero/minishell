/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:21:25 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:21:26 by rbraaksm      ########   odam.nl         */
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
