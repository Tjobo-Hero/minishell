/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 11:40:37 by tvan-cit       #+#    #+#                */
/*   Updated: 2019/11/14 11:11:45 by tvan-cit      ########   odam.nl         */
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
