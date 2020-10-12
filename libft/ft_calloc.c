/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/08 12:29:05 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/10/09 15:13:06 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	ptr = (char*)malloc(size * count);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, (size * count));
	return (ptr);
}
