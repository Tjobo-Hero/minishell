/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 11:40:37 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/07/16 18:34:44 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int lstsize;

	if (lst != 0)
	{
		lstsize = 1;
		while (lst->next != 0)
		{
			lstsize++;
			lst = lst->next;
		}
		return (lstsize);
	}
	return (0);
}
