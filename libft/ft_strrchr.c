/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 09:36:17 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/07/16 18:37:05 by rbraaksm      ########   odam.nl         */
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
