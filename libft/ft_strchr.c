/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 17:51:06 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/18 11:00:29 by rbraaksm      ########   odam.nl         */
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
