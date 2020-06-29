/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 14:19:31 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/29 12:17:01 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**copy_env(t_mini *d, char **str, int x, int c)
{
	char	**tmp;
	int i;

	i = 0;
	if (c == 1)
		tmp = (char **)malloc(sizeof(char *) * (x + 2));
	else
		tmp = (char **)malloc(sizeof(char *) * (x + 1));
	// if (tmp == NULL)
	// 	return (malloc_error());
	while (i < x)
	{
		tmp[i] = ft_strdup(str[i]);
		// if (tmp[i] == NULL)
		// 	return (malloc_error());
		i++;
	}
	if (c == 1)
		return (tmp);
	tmp[i] = NULL;
	return (tmp);
}

void	free_list(t_mini *d, char **tmp)
{
	int		i;

	i = d->c_env;
	while (i > 0)
	{
		free(tmp[i - 1]);
		i--;
	}
	free(tmp);
}

void	last_alpha(char **env_copy, int *i)
{
	char *temp;

	while (env_copy[*i][0] > env_copy[*i + 1][0])
	{
		temp = env_copy[*i];
		env_copy[*i] = env_copy[*i + 1];
		env_copy[*i + 1] = temp;
		if (env_copy[*i + 1] == NULL)
			break ;
		(*i)++;
	}
	(*i) = 0;
}

void	same_first_letter(char **env_copy, int *i)
{
	char	*temp;
	int		i_2;

	i_2 = 0;
	while (env_copy[*i][i_2] == env_copy[*i + 1][i_2] && env_copy[*i][i_2] != 0)
		i_2++;
	if (env_copy[*i][i_2] > env_copy[*i + 1][i_2])
	{
		temp = env_copy[*i];
		env_copy[*i] = env_copy[*i + 1];
		env_copy[*i + 1] = temp;
		(*i) = 0;
	}
	else
		(*i)++;
}

void	print_export(t_mini *d)
{
	int i;
	int k;
	int is_count;

	i = 0;
	while (d->exp[i])
	{
		ft_printf("declare -x ");
		k = 0;
		is_count = 0;
		while (d->exp[i][k])
		{
			write(1, &d->exp[i][k], 1);
			if (d->exp[i][k] == '=' && is_count == 0)
			{
				write(1, "\"", 1);
				is_count = 1;
			}
			k++;
		}
		write(1, "\"\n", 2);
		i++;
	}
}

int		**env_alpha(t_mini *d)
{
	int i;

	i = 0;
	while (d->exp[i + 1] != NULL)
	{
		if (d->exp[i][0] == d->exp[i + 1][0])
			same_first_letter(d->exp, &i);
		else if (d->exp[i][0] > d->exp[i + 1][0])
			last_alpha(d->exp, &i);
		else
			i++;
	}
	print_export(d);
	return (0);
}

void	new_list(t_mini *d, char *str, int i)
{
	char	**tmp;

	if (i == 1)
	{
		tmp = copy_env(d, d->env, d->c_env, 0);
		free_list(d, d->env);
		d->env = copy_env(d, tmp, d->c_env, 1);
		d->env[d->c_env] = ft_strdup(str);
		d->env[d->c_env + 1] = NULL;
		d->c_env++;
		free_list(d, tmp);
		tmp = copy_env(d, d->exp, d->c_exp, 0);
		free_list(d, d->exp);
		d->exp = copy_env(d, tmp, d->c_exp, 1);
		d->exp[d->c_exp] = ft_strdup(str);
		d->exp[d->c_exp + 1] = NULL;
		d->c_exp++;
	}
	else
	{
		tmp = copy_env(d, d->exp, 0);
		free_list(d, d->exp);
		d->exp = copy_env(d, tmp, 1);
		d->exp[d->c_env] = ft_strdup(str);
		d->exp[d->c_env + 1] = NULL;
	}
	free_list(d, tmp);
}

int		**export(t_mini *d)
{
	int		a;
	
	a = 1;
	if (d->exp == NULL)
		d->exp = copy_env(d, d->env, d->c_env, 0);
	if (!d->args[1])
		return (env_alpha(d));
	while (d->args[a])
	{
		// first_part(d, d->args[a]);
		if (ft_strchr(d->args[a], '='))
			new_list(d, d->args[a], 1);
		else
			new_list(d, d->args[a], 0);
		a++;
	}
	int x = 0;
	while (d->env[x])
	{
		ft_printf("after : %s\n", d->env[x]);
		x++;
	}
	return (NULL);
}
