/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_array.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 14:14:22 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/26 16:09:30 by rbraaksm      ########   odam.nl         */
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
	tmp == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
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
	char	tmp[PATH_MAX];
	char	*find;
	int		count;

	(*i)++;
	count = 0;
	if (d->orig[row][*i] == '?')
		return (ret_str(d, str, &d->orig[row][*i], i));
	find = find_dollar(d, &d->orig[row][*i], &count);
	ft_bzero(tmp, PATH_MAX + 1);
	ft_strlcpy(tmp, str, (*i));
	if (d->orig[row][*i + count] == '\"')
		ft_strlcpy(&tmp[*i - 1], &d->orig[row][*i + count], 2);
	if (find != NULL)
	{
		ft_strlcpy(&tmp[*i - 1], find, ft_strlen(find) + 1);
		ft_strlcpy(&tmp[ft_strlen(tmp)], &d->orig[row][*i + count],
		ft_strlen(&d->orig[row][*i + count]) + 1);
	}
	(*i) = (count);
	free(str);
	str = ft_strdup(tmp);
	return (str);
}

void		set_on_off(int *doub, int *single, char c)
{
	if (c == '\"' && *single == -1)
		(*doub) *= -1;
	else if (c == '\'' && *doub == -1)
		(*single) *= -1;
}

static void	set_null(int *single, int *doub, int *y, int *set)
{
	(*single) = -1;
	(*doub) = -1;
	(*y) = 0;
	(*set) = 0;
}

static void	free_str(t_mini *d, int *y)
{
	if (d->orig[*y][0] == '\0')
	{
		free(d->orig[*y]);
		d->orig[*y] = NULL;
		free(d->orig[*y + 1]);
	}
	(*y)++;
}

void		update_array(t_mini *d)
{
	int	single;
	int	doub;
	int	y;
	int	x;
	int	set;

	set_null(&single, &doub, &y, &set);
	while (d->orig[y])
	{
		x = 0;
		while (d->orig[y][x] != '\0')
		{
			if (d->orig[y][x] == '\\' && set == 0)
				set = 1;
			else if ((d->orig[y][x] == '\"' || d->orig[y][x] == '\'') && !set)
				set_on_off(&doub, &single, d->orig[y][x]);
			else if (d->orig[y][x] == '$' && !set && single == -1 &&
					(ft_isalnum(d->orig[y][x + 1]) || d->orig[y][x + 1] == '?'
					|| d->orig[y][x + 1] == '_'))
				d->orig[y] = create_new_str(d, d->orig[y], &x, y);
			else
				set = 0;
			x++;
		}
		free_str(d, &y);
	}
}
