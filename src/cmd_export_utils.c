/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 19:50:17 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/07/17 18:00:14 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_str(t_mini *d, char *str, char *arg)
{
	char	c;
	int		i;
	int		x;

	i = 0;
	x = 0;
	c = ' ';
	while (arg[i] != '\0')
	{
		if ((arg[i] == '\'' || arg[i] == '\"') && d->set == 0)
		{
			d->set = 1;
			c = arg[i];
		}
		else if ((arg[i] == '\'' || arg[i] == '\"') && arg[i] == c)
		{
			d->set = 0;
			c = ' ';
		}
		else if (((arg[i] == '\'' || arg[i] == '\"') && arg[i] != c && d->set == 0))
		{
			str[x] = arg[i];
			x++;
		}
		else if (arg[i] != '\'' || arg[i] != '\"')
		{
			str[x] = arg[i];
			x++;
		}
		i++;
	}
}

char	*check_arg(t_mini *d, char *arg)
{
	char	str[PATH_MAX];
	char	c;
	int		i;
	int		is;

	i = 0;
	is = 0;
	c = ' ';
	d->set = 0;
	fill_str(d, str, arg);
	printf("str: %s\n", str);
	while (arg[i] != '\0')
	{
		if ((arg[i] == '\'' || arg[i] == '\"') && c == ' ')
		{
			d->set += 1;
			c = arg[i];
		}
		else if ((arg[i] == '\'' || arg[i] == '\"') && arg[i] == c)
		{
			d->set = 0;
			c = ' ';
		}
		else if (i > 0 && arg[i] == '=' && is < 1)
			is += 1;
		else if (i > 0 && (arg[i] == '\'' || arg[i] == '\"' || arg[i]== '\\') && arg[i] != c && is == 0 && d->set > 1)
			return (NULL);
		else if (is == 0 && (arg[i] < 65 || (arg[i] > 90 && arg[i] < 95) || (arg[i] > 95 && arg[i] < 97) || arg[i] > 122))
			return (NULL);
		i++;
	}
	if (d->set == 1)
		return (NULL);
	clear_str(str);
	return ("h");
}

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

	str = check_arg(d, arg);
	if (str == NULL)
		printf("bash: export: `%s': not a valid identifier\n", arg);
	str = arg;
	set_env(&d->list[d->index], str, d->index);
	d->list[d->index].alpha = find_lowest(d->echo, &d->list[d->index],
	d->index);
	set_alpha(d->echo, d->list[d->index].alpha);
	hash_table_insert_index(&d->list[d->index], d->echo,
	hash_echo(d->list[d->index].head));
	d->index++;
	// free(str);
}
