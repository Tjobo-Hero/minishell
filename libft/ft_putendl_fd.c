/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 10:07:44 by tvan-cit       #+#    #+#                */
/*   Updated: 2019/11/13 10:11:08 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
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
	ft_putchar_fd('\n', fd);
}
