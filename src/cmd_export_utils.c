/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 19:50:17 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/16 20:45:19 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*str_double(t_mini *d, char *arg, int i)
// {
// 	char	*str;

// 	while (arg[i] != '\0')
// 	{
// 		if (str[i - 1] != '\\' && (str[i] == '\"' || str[i] == "\'" || str[i] == '\\'))
// 			set_on_off(d, str[i]);
// 		if (set == 0)
// 			break ;
// 		if (str[i] == '\\' && str)
// 		i++;
// 	}
// 	}
// }

// char	*make_list(t_mini *d, char *arg)
// {
// 	int		i;
// 	int		x;

// 	i = 0;
// 	d->singleq = 0;
// 	d->doubleq = 0;
// 	d->slash = 0;
// 	d->set = ' ';
// 	while (str[i] != '\0' && str[i] != '=')
// 		i++;
// 	if (str[i] == '=')
// 		x = i + 1;
// 	if (str[i] == '\"')
// 		return (str_double(d, arg, x));
// 	return (NULL);
// }

int		find_lowest(t_env **echo, t_env *new, int cmp)
{
	t_env	*tmp;
	int		i;
	int		c;

	i = 0;
	c = 0;
	tmp = NULL;
	while (i < ECHO)
	{
		if (echo[i])
		{
			tmp = echo[i];
			while (tmp)
			{
				c = ft_strncmp(new->head, tmp->head, ft_strlen(new->head));
				if (c < 0 && tmp->alpha < cmp)
					cmp = tmp->alpha;
				if (c == 0 && cmp > tmp->alpha)
					cmp = tmp->alpha;
				tmp = tmp->next;
			}
		}
		i++;
	}
	return (cmp);
}

void	set_alpha(t_env **echo, int cmp)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (i < ECHO)
	{
		if (echo[i])
		{
			tmp = echo[i];
			while (tmp)
			{
				if (tmp->alpha >= cmp)
					tmp->alpha++;
				tmp = tmp->next;
			}
		}
		i++;
	}
}

void	new_list(t_mini *d, char *arg)
{
	char 	*str;
	int		i;

	i = 0;
	if (arg[0] < 65 || (arg[0] > 90 && arg[0] < 95) ||
		(arg[0] > 95 && arg[0] < 97) || arg[0] > 122)
		return ;
	// str = make_list(d, arg);
	str = arg;
	set_env(&d->list[d->index], str, d->index);
	d->list[d->index].alpha = find_lowest(d->echo, &d->list[d->index],
	d->index);
	set_alpha(d->echo, d->list[d->index].alpha);
	hash_table_insert_index(&d->list[d->index], d->echo,
	hash_echo(d->list[d->index].head));
	d->count++;
	d->index++;
	// free(str);
}
