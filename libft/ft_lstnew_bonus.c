/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:19:45 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:19:46 by rbraaksm      ########   odam.nl         */
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
