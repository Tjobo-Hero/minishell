/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 13:50:06 by rbraaksm      #+#    #+#                 */
/*   Updated: 2019/11/15 08:59:26 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		ft_count_words(char *s, char c)
{
	int		count;
	int		index;

	count = 0;
	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] != c && (s[index + 1] == c || s[index + 1] == '\0'))
			count++;
		index++;
	}
	return (count);
}

static char		*word_malloc(char const *s, int c)
{
	char	*new_str;
	int		index;

	index = 0;
	while (s[index] && s[index] != c)
		index++;
	new_str = (char *)malloc(sizeof(char) * (index + 1));
	if (!new_str)
		return (NULL);
	index = 0;
	while (s[index] && s[index] != c)
	{
		new_str[index] = s[index];
		index++;
	}
	new_str[index] = '\0';
	return (new_str);
}

static int		ft_free(char **array, int words)
{
	while (words >= 0)
	{
		free(array[words]);
		words--;
	}
	free(array);
	return (0);
}

static int		ft_fill(char *s, char **new_arr, char c)
{
	int		i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			new_arr[i] = word_malloc((char*)s, c);
			if (!new_arr[i])
				return (ft_free(new_arr, i - 1));
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (1);
}

char			**ft_split(char const *s, char c)
{
	char	**new_arr;
	int		words;
	int		succes;

	succes = 0;
	if (!s)
		return (NULL);
	words = ft_count_words((char*)s, c);
	new_arr = (char **)malloc(sizeof(char*) * (words + 1));
	if (!new_arr)
		return (NULL);
	succes = ft_fill((char*)s, new_arr, c);
	if (succes == 0)
		return (NULL);
	new_arr[words] = ((void*)0);
	return (new_arr);
}
