/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memalloc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 09:47:16 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/16 18:35:42 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void *temp;

	temp = malloc(size);
	if (temp <= 0)
		return (NULL);
	ft_bzero(temp, size);
	return (temp);
}
