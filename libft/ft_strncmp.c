/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:21:43 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:21:44 by rbraaksm      ########   odam.nl         */
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
