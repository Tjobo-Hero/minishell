/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 14:14:22 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/22 15:08:03 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_dollar(t_mini *d, char *find)
{
	t_env	*tmp;

	tmp = look_up(find, d->echo);
	if (tmp == NULL)
		return (NULL);
	return (tmp->list);
}

static char	*create_new_str(t_mini *d, char *str, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = find_dollar(d, &str[i + 1]);
	if (tmp2 == NULL)
		return (str);
	tmp = ft_calloc((ft_strlen(tmp2) + (i - 1)), sizeof(char*));
	tmp == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	ft_strlcpy(tmp, str, i + 1);
	ft_strlcpy(&tmp[i], tmp2, ft_strlen(tmp2) + 1);
	free(str);
	return (tmp);
}

void	update_array(t_mini *d)
{
	int	i;
	int	y;
	int	z;

	i = 0;
	while (d->orig[i])
	{
		z = 0;
		y = 0;
		while (d->orig[i][z] != '\0')
		{
			if (d->orig[i][z] == '\\')
				y++;
			if (d->orig[i][z] == '$' && (y % 2 == 0))
				d->orig[i] = create_new_str(d, d->orig[i], z);
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
