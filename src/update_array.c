/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 14:14:22 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/23 15:42:05 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ret_str(t_mini *d, char *str, char *find, int *i)
{
	char	*tmp;
	char	new[PATH_MAX];

	ft_bzero(new, PATH_MAX + 1);
	if (str[0] != '$')
		ft_strlcpy(new, str, (*i));
	tmp = ft_itoa(d->ret);
	(*i) = ft_strlen(tmp) - 1;
	ft_strlcpy(&new[ft_strlen(new)], tmp, ft_strlen(tmp) + 1);
	ft_strlcpy(&new[ft_strlen(new)], &find[1], ft_strlen(&find[1]) + 1);
	free(tmp);
	free(str);
	str = ft_strdup(new);
	return (str);
}

static char	*find_dollar(t_mini *d, char *find, int *i)
{
	t_env	*tmp;
	char	new[PATH_MAX];

	ft_bzero(new, (PATH_MAX + 1));
	while (find[*i] != '\0' && (ft_isalnum(find[*i]) || find[*i] == '_'))
		(*i)++;
	ft_strlcpy(new, find, (*i + 1));
	tmp = look_up(new, d->echo);
	if (tmp == NULL)
		return (NULL);
	return (tmp->list);
}

static char	*create_new_str(t_mini *d, char *str, int *i, int row)
{
	char	*tmp;
	char	*find;
	int		count;

	(*i)++;
	count = 0;
	if (d->orig[row][*i] == '?')
		return (ret_str(d, str, &d->orig[row][*i], i));
	find = find_dollar(d, &d->orig[row][*i], &count);
	if (find == NULL)
		tmp = ft_calloc((count + 1), sizeof(char*));
	else
		tmp = ft_calloc((ft_strlen(find) + (count)), sizeof(char*));
	tmp == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	ft_strlcpy(tmp, str, (*i));
	if (find != NULL)
	{
		ft_strlcpy(&tmp[*i - 1], find, ft_strlen(find) + 1);
		ft_strlcpy(&tmp[ft_strlen(tmp)], &d->orig[row][*i + count],
		ft_strlen(&d->orig[row][*i + count]) + 1);
	}
	(*i) = (count);
	free(str);
	return (tmp);
}

static void	check_dollar(t_mini *d, int i, int *y, int *z)
{
	char	**tmp;

	tmp = d->orig;
	if (tmp[i][*z] == '\\')
		(*y)++;
	if (tmp[i][*z] == '$' && (*y % 2 == 0) && (ft_isalnum(tmp[i][*z + 1])
		|| tmp[i][*z + 1] == '?' || tmp[i][*z + 1] == '_'))
	{
		tmp[i] = create_new_str(d, tmp[i], z, i);
		*y = 0;
	}
}

void		update_array(t_mini *d)
{
	int		i;
	int		y;
	int		z;

	i = 0;
	while (d->orig[i])
	{
		z = 0;
		y = 0;
		while (d->orig[i][z] != '\0')
		{
			check_dollar(d, i, &y, &z);
			z++;
		}
		if (d->orig[i][0] == '\0')
		{
			free(d->orig[i]);
			d->orig[i] = NULL;
			free(d->orig[i + 1]);
		}
		i++;
	}
}
