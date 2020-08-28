/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 14:19:31 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/08/28 14:53:22 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		**print(t_env **echo)
{
	t_env	*tmp;
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (i < ECHO)
	{
		if (echo[i] != NULL)
		{
			tmp = echo[i];
			while (tmp)
			{
				if (tmp->alpha == c)
					break ;
				tmp = tmp->next;
			}
		}
		if (tmp != NULL && tmp->alpha == c)
		{
			ft_printf("declare -x %s", tmp->head);
			tmp->set ? write(1, "=\"", 2) : 0;
			ft_printf("%s", tmp->echo);
			tmp->set ? write(1, "\"", 1) : 0;
			write(1, "\n", 1);
			i = 0;
			c++;
		}
		else
			i++;
	}
	return (0);
}

int		replace(t_mini *d, t_env *tmp, int a, int len)
{
	int		i;

	if (d->args[a][len] == '\0')
		return (0);
	i = ft_strlen(d->args[a]);
	tmp->set = 0;
	if (d->args[a][len] == '=')
		tmp->set = 1;
	d->list[tmp->index].set = tmp->set;
	clear_str(d->list[tmp->index].list);
	clear_str(d->list[tmp->index].echo);
	ft_strlcpy(d->list[tmp->index].list, d->args[a], i + 1);
	ft_strlcpy(d->list[tmp->index].echo, &d->args[a][len + 1], (i - len));
	return (0);
}

int		check_cmp(t_mini *d, int a)
{
	t_env	*tmp;
	char	*str;
	int		i;
	int		len;

	len = 0;
	i = 0;
	str = NULL;
	while (d->args[a][len] != '=' && d->args[a][len] != '\0')
		len++;
	if (d->args[a][len] == '=')
	{
		str = malloc(sizeof(char *) * len);
		str == NULL ? int_malloc_error() : 0;
		ft_strlcpy(str, d->args[a], len + 1);
	}
	else
		str = ft_strdup(d->args[a]);
	tmp = look_up(str, d->echo);
	if (tmp == NULL)
		return (1);
	free(str);
	return (replace(d, tmp, a, len));
}

int		**export(t_mini *d)
{
	int	a;

	a = 1;
	// if (!d->args[1])
	// 	return (print(d->echo));
	// while (d->args[a])
	// {
	// 	if (check_cmp(d, a) == 1)
	// 		new_list(d, d->args[a]);
	// 	a++;
	// }
	char *str;
	str = check_arg(d, d->args[a]);
	if (str == NULL)
		printf("error\n");
	printf("\n");
	return (NULL);
}
