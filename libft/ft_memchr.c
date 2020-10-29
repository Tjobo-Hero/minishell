/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:20:05 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:20:06 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = NULL;
	while (i < n)
	{
		if (((unsigned char*)s)[i] == (unsigned char)c)
		{
			ptr = (unsigned char*)&s[i];
			return (ptr);
		}
		i++;
	}
	return (ptr);
}
