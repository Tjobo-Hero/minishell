/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 16:57:07 by tvan-cit       #+#    #+#                */
/*   Updated: 2019/11/13 10:05:54 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int		index_s;

	if (!s)
		return ;
	index_s = 0;
	while (s[index_s] != '\0')
	{
		ft_putchar_fd(s[index_s], fd);
		index_s++;
	}
}
