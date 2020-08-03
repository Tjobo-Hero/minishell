/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 19:50:17 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/08/03 09:55:07 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_first(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (arg[i] < 65 || (arg[i] > 90 && arg[i] < 95) ||
		(arg[i] > 95 && arg[i] < 97) || arg[i] > 122)
			return (0);
		i++;
	}
	return (1);
}

int		check2(char *arg)
{
	int i;
	int s;
	int dou;
	int slash;

	i = 0;
	s = 1;
	dou = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] != '\\' && arg[i - 1] != '\\')
			slash = 0;
		else if (arg[i] == '\\')
			slash++;
		if (arg[i] == '\'' && slash % 2 == 0 && dou != -1)
			s *= -1;
		else if (arg[i] == '\"' && slash % 2 == 0 && s != -1)
			dou *= -1;
		i++;
	}
	if (dou == -1 || s == -1 || arg[i - 1] == '\\')
		return (0);
	return (1);
}

void	fill(char *str, char *arg, int *i, int *x)
{
	char	c;

	c = arg[*i];
	*i = *i + 1;
	while (arg[*i] != '\0')
	{
		if (arg[*i] == c)
			break;
		if (c == '\'' && arg[*i] == '\\')
		{
			str[*x] = '\\';
			*x = *x + 1;
		}
		str[*x] = arg[*i];
		*x = *x + 1;
		*i = *i + 1;
	}
	*i = *i + 1;
}

char	*check_arg(t_mini *d, char *arg)
{
	char	str[PATH_MAX];
	char	*tmp;
	int		i;
	int		x;

	i = 0;
	x = 0;
	(void)d;
	if (check2(arg) == 0)
		return (NULL);
	while (arg[i] != '\0')
	{
		if (arg[i] == '\'' && arg[i - 1] != '\\')
			fill(str, arg, &i, &x);
		else if (arg[i] == '\"' && arg[i - 1] != '\\')
			fill(str, arg, &i, &x);
		else
		{
			str[x] = arg[i];
			x++;
			i++;
		}
	}
	printf("string: %s\n", str);
	tmp = str;
	clear_str(str);
	return (tmp);
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
