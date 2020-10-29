/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:21:59 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:22:00 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_begin(char const *s1, char const *set)
{
	int begin;
	int	i;
	int i2;
	int	sign;

	begin = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		i2 = 0;
		sign = 0;
		while (set[i2] != '\0')
		{
			if (set[i2] == s1[i])
			{
				sign = 1;
				begin++;
			}
			i2++;
		}
		if (sign == 0)
			break ;
		i++;
	}
	return (begin);
}

static int		ft_end(char const *s1, char const *set)
{
	int		end;
	size_t	i;
	int		i2;
	int		sign;

	end = 0;
	i = (ft_strlen(s1) - 1);
	while (i > 0)
	{
		i2 = 0;
		sign = 0;
		while (set[i2] != '\0')
		{
			if (set[i2] == s1[i])
			{
				sign = 1;
				end++;
			}
			i2++;
		}
		if (sign == 0)
			break ;
		i--;
	}
	return (end);
}

static char		*ft_copy(char *newstr, char const *s1, size_t begin, size_t end)
{
	size_t	i;
	int		i2;

	i = begin;
	i2 = 0;
	while (begin < (end - 1))
	{
		newstr[i2] = s1[i];
		i++;
		i2++;
		begin++;
	}
	newstr[i2] = '\0';
	return (newstr);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	size_t	begin;
	size_t	end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	begin = ft_begin(s1, set);
	end = ft_end(s1, set);
	if (begin == (ft_strlen(s1)))
		return (ft_strdup(""));
	newstr = (char*)malloc(sizeof(char) *
	(ft_strlen(s1) - (begin + end) + 1));
	end = (ft_strlen(s1) - (end) + 1);
	if (newstr == NULL)
		return (NULL);
	return (ft_copy(newstr, s1, begin, end));
}
