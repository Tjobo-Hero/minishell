/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/08 15:44:56 by tvan-cit       #+#    #+#                */
/*   Updated: 2019/11/08 16:48:38 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		i2;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	i2 = 0;
	newstr = ((char*)malloc(sizeof(char) *
	((ft_strlen(s1) + ft_strlen(s2)) + 1)));
	if (!newstr)
		return (NULL);
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[i2] != '\0')
	{
		newstr[i] = s2[i2];
		i++;
		i2++;
	}
	newstr[i] = '\0';
	return (newstr);
}
