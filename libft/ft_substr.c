/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/08 13:00:19 by tvan-cit       #+#    #+#                */
/*   Updated: 2019/11/15 11:20:57 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	lens;
	size_t	i;

	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	if (start > lens)
		return (ft_strdup(""));
	sub = (char*)malloc(sizeof(char) * len + 1);
	i = 0;
	if (sub == NULL)
		return (0);
	while (s[i] != '\0' && i < len)
	{
		sub[i] = s[start];
		start++;
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
