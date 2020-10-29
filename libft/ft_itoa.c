/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:19:02 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:19:03 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int		ft_number_count(int n)
{
	int		numbercount;

	numbercount = 0;
	if (n == 0 || n == -0)
		return (2);
	if (n < 0)
	{
		numbercount++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		numbercount++;
	}
	return (numbercount);
}

static char		*ft_transform_int_to_char(char *str, int n)
{
	int index_str;

	index_str = ft_number_count(n);
	str = (char*)malloc(sizeof(char) * (ft_number_count(n) + 1));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	str[index_str] = '\0';
	index_str--;
	while (n > 0)
	{
		str[index_str] = n % 10 + '0';
		n = n / 10;
		index_str--;
	}
	return (str);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		exception;

	exception = 0;
	str = NULL;
	if (n == 0 || n == -0)
	{
		str = (char*)malloc(sizeof(char) * (ft_number_count(n)));
		if (str == NULL)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (n == -2147483648)
	{
		n = (n - 1) * -1;
		exception = 1;
	}
	str = ft_transform_int_to_char(str, n);
	if (exception == 1)
		str[ft_number_count(n) - 1] = '8';
	return (str);
}
