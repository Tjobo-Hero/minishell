/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:22:06 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:22:10 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	lens;
	size_t			i;

	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	if (start > lens)
		return (ft_strdup(""));
	if (lens < len)
		len = (size_t)lens;
	sub = (char*)malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (0);
	i = 0;
	while (s[start] && i < len)
	{
		sub[i] = s[start];
		start++;
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
