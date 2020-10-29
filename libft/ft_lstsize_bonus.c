/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:19:51 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:19:52 by rbraaksm      ########   odam.nl         */
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
