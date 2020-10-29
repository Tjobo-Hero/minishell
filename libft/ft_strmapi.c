/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:21:36 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:21:37 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		index;
	char	*newstr;

	if (!s)
		return (NULL);
	newstr = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (newstr == NULL)
		return (NULL);
	index = 0;
	while (s[index] != '\0')
	{
		newstr[index] = f(index, s[index]);
		index++;
	}
	newstr[index] = '\0';
	return (newstr);
}
