/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:20:39 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:20:40 by rbraaksm      ########   odam.nl         */
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
