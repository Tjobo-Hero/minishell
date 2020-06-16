/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_string_utils_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 16:41:22 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/08 12:33:27 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_putstring(char *s)
{
	int count;

	count = ft_strlen(s);
	if (s != NULL)
		write(1, s, ft_strlen(s));
	return (count);
}

int		ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int		i;
	const unsigned char	*ps1;
	const unsigned char	*ps2;

	i = 0;
	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (ps1[i] != '\0' && ps2[i] != '\0' && (ps1[i] == ps2[i]) && i < n)
	{
		if (ps1[i] != ps2[i])
			return (ps1[i] - ps2[i]);
		i++;
	}
	if (ps1[i] != ps2[i] && i != n)
		return (ps1[i] - ps2[i]);
	return (0);
}
