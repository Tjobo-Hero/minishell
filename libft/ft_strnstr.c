/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:21:47 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:21:48 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char		*ptr;
	size_t		i;
	int			i2;

	i = 0;
	i2 = 0;
	if (ft_strlen((char*)needle) == 0)
		return ((char*)haystack);
	if (ft_strlen((char*)haystack) == 0)
		return (NULL);
	while (haystack[i] != '\0' && i <= len)
	{
		while (haystack[i + i2] == needle[i2] && (i + i2) < len)
		{
			if (!needle[i2 + 1])
			{
				ptr = (char*)&haystack[i];
				return (ptr);
			}
			i2++;
		}
		i2 = 0;
		i++;
	}
	return (0);
}
