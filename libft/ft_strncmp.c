/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 09:25:33 by tvan-cit       #+#    #+#                */
/*   Updated: 2019/11/14 11:42:28 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] == s1[i] && n > 1)
	{
		i++;
		n--;
	}
	res = (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
	return (res);
}
