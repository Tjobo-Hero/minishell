/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 14:19:31 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/26 15:35:33 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		copy_env(t_mini *d)
{
	int i;

	i = 0;
	d->env_copy = (char **)malloc(sizeof(char *) * (d->c_env));
	if (d->env_copy == NULL)
		return (malloc_error());
	while (i < d->c_env)
	{
		d->env_copy[i] = ft_strdup(d->env[i]);
		if (d->env[i] == NULL)
			return (malloc_error());
		i++;
	}
	return (0);
}

void	last_alpha(char **tmp, int *i)
{
	char *temp;

	while (tmp[*i][0] > tmp[*i + 1][0])
	{
		temp = tmp[*i];
		tmp[*i] = tmp[*i + 1];
		tmp[*i + 1] = temp;
		if (tmp[*i + 1] == NULL)
			break ;
		(*i)++;
	}
	(*i) = 0;
}

int		**env_alpha(t_mini *d)
{
	int i;
	int s;
	char **tmp;

	tmp = d->env;
	i = 0;
	s = 0;
	while (tmp)
	{
		ft_printf("TEMP: %s\n", tmp[s]);
		s++;
	}
	while (tmp[i + 1])
	{
		if (tmp[i][0] > tmp[i + 1][0])
			last_alpha(tmp, &i);
		// else if (tmp[i][0] == tmp[i + 1][0])
		// 	same(tmp, &i);
		// else
		// 	i++;
	}
	s = 0;
	ft_printf("------------------------------\n");
	while (tmp[s])
	{
		ft_printf("NEW:%s\n", tmp[s]);
		s++;
	}
	return ((int**)1);
}

char	*first(char *str, int i)
{
	char	*tmp;
	int		x;

	x = 0;
	tmp = malloc(sizeof(char *) * (i + 1));
	if (tmp == NULL)
		return (NULL);
	while (x < i)
	{
		tmp[x] = str[x];
		x++;
	}
	tmp[x] = '\0';
	return (tmp);
}

char	*new_env(t_mini *d, char *str, int i)
{
	char	*tmp;

	tmp = first(str, i);
	(void)d;
	return (tmp);
}

char	*new_exp(t_mini *d, char *str, int i)
{
	char	*tmp;

	tmp = first(str, i);
	(void)d;
	return (tmp);
}

char	*first_part(t_mini *d, char *str)
{
	char	*tmp;
	int	i;

	i = 0;
	tmp = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '=' && str[i - 1] != ' ')
			return (new_env(d, str, (i + 1)));
		if (str[i] == ' ')
			return (new_exp(d, str, i));
		i++;
	}
	return (first(str, i));
		
}

int		**export(t_mini *d)
{
	char	*tmp;
	int		a;
	
	a = 1;
	if (d->env_copy == NULL)
		copy_env(d);
	if (!d->args[1])
		return (env_alpha(d));
	tmp = first_part(d, d->args[a]);
	ft_printf("new = %s\n", tmp);
	free(tmp);
	// while (d->args[a])
	// {
	// 	e = 0;
	// 	while (d->env[e])
	// 	{
	// 		if (!(ft_strncmp(d->env[e], d->args[a], ft_strlen(d->env[e]))))
	// 			replace(d, );
			
	// 	}
	// }
// 	ft_printf("malloc fail env_copy");
// // 		exit(1);
	return (NULL);
}
