/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 10:07:44 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/07/16 18:36:15 by rbraaksm      ########   odam.nl         */
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
