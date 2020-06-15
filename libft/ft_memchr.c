/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 11:25:51 by tvan-cit       #+#    #+#                */
/*   Updated: 2019/11/07 11:44:52 by tvan-cit      ########   odam.nl         */
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
