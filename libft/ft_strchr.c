/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 17:51:06 by tvan-cit       #+#    #+#                */
/*   Updated: 2019/11/14 15:31:13 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = NULL;
	while (*s)
	{
		if (*s == c)
		{
			ptr = (char*)s;
			return (ptr);
		}
		s++;
	}
	if (c == '\0')
		return ((char*)s);
	return (ptr);
}
