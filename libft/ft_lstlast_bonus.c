/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:19:35 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:19:36 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstlast(t_list *lst)
{
	if (lst == 0)
		return (lst);
	while (lst->next != 0)
	{
		lst = lst->next;
	}
	return (lst);
}
