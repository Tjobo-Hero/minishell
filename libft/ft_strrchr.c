/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:21:54 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:21:55 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = NULL;
	while (*s)
	{
		if (*s == c)
			ptr = (char*)s;
		s++;
	}
	if (ptr)
		return (ptr);
	if (c == '\0')
		return ((char*)s);
	return (0);
}
