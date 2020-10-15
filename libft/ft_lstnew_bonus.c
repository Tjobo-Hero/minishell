/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 10:56:42 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/07/16 18:35:30 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void *content)
{
	t_list *list_new;

	list_new = (t_list*)malloc(sizeof(t_list));
	if (list_new == NULL)
		return (NULL);
	list_new->content = content;
	list_new->next = 0;
	return (list_new);
}
