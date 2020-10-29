/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha_str.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:18:33 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:18:34 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalpha_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
