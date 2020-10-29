/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:18:12 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:18:15 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*tmp;

	tmp = (char*)s;
	i = 0;
	while (i < n)
	{
		tmp[i] = '\0';
		i++;
	}
}
