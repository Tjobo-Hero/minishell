/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/09 15:04:05 by tvan-cit       #+#    #+#                */
/*   Updated: 2019/11/15 17:37:52 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char		**ft_freenewstr(char **newstr, int i_n)
{
	while (newstr)
	{
		i_n--;
		free(newstr[i_n]);
	}
	free(newstr);
	return (NULL);
}

static int		ft_letter(char const *s, char c, int i_s)
{
	int lettercount;

	lettercount = 0;
	while (s[i_s] != c && s[i_s] != '\0')
	{
		lettercount++;
		i_s++;
	}
	return (lettercount);
}

static int		ft_word_count(char const *s, char c)
{
	int i_s;
	int totalwordcount;

	i_s = 0;
	totalwordcount = 0;
	while (s[i_s] != '\0')
	{
		while (s[i_s] == c && s[i_s] != '\0')
			i_s++;
		if (s[i_s] != c && s[i_s] != '\0')
		{
			totalwordcount++;
			while (s[i_s] != c && s[i_s] != '\0')
				i_s++;
		}
	}
	return (totalwordcount);
}

static char		**ft_createstr(char const *s, char c, char **newstr)
{
	int	i_s;
	int	i_n;
	int	i2_n;

	i_s = 0;
	i_n = 0;
	while (s[i_s] != '\0' && i_n < ft_word_count(s, c))
	{
		i2_n = 0;
		while (s[i_s] != '\0' && s[i_s] == c)
			i_s++;
		newstr[i_n] = (char*)malloc(sizeof(char) * (ft_letter(s, c, i_s) + 1));
		if (newstr[i_n] == NULL)
			return (ft_freenewstr(newstr, i_n));
		while (s[i_s] != '\0' && s[i_s] != c)
		{
			newstr[i_n]	[i2_n] = s[i_s];
			i2_n++;
			i_s++;
		}
		newstr[i_n]	[i2_n] = '\0';
		i_n++;
	}
	newstr[i_n] = NULL;
	return (newstr);
}

char			**ft_split(char const *s, char c)
{
	char	**newstr;

	if (!s)
		return (NULL);
	newstr = (char**)malloc(sizeof(char*) * (ft_word_count(s, c) + 1));
	if (newstr == NULL)
		return (NULL);
	ft_createstr(s, c, newstr);
	return (newstr);
}
