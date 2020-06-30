/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 14:19:31 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/06/30 12:06:18 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**copy_env(char **str, int x, int c)
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
	}
	else
		(*i)++;
}

void	print_export(char **tmp)
{
	int i;
	int k;
	int is_count;

	i = 0;
	while (tmp[i])
	{
		ft_printf("declare -x ");
		k = 0;
		while (tmp[i][k])
		{
			is_count = 0;
			write(1, &tmp[i][k], 1);
			if (tmp[i][k] == '=' && is_count == 0)
			{
				write(1, "\"", 1);
				is_count = 1;
			}
			k++;
		}
		if (ft_strchr(tmp[i], '='))
				write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
}

void	swap(t_mini *d, int i)
{
	char *tmp;

	tmp = d->exp[i];
	d->exp[i] = d->exp[i + 1];
	d->exp[i + 1] = tmp;
}

int		**env_alpha(t_mini *d)
{
	int i;

	i = 0;
	d->exp = copy_env(d->env, d->c_env, 0);
	// while (d->exp[i + 1] != NULL)
	// {
	// 	if (d->exp[i][0] == d->exp[i + 1][0])
	// 		same_first_letter(d->exp, &i);
	// 	else if (d->exp[i][0] > d->exp[i + 1][0])
	// 		last_alpha(d->exp, &i);
	// 	else
	// 		i++;
	// }
	while (d->exp[i + 1] != NULL)
	{
		while (ft_strncmp(d->exp[i], d->exp[i + 1], ft_strlen(d->exp[i])) > 0)
		{
			swap(d, i);
			i = 0;	
		}
		i++;
	}
	print_export(d->exp); 
	free_list(d, d->exp);
	return (0);
}

void	new_list(t_mini *d, char *str)
{
	char	**tmp;

	tmp = copy_env(d->env, d->c_env, 0);
	// free_list(d, d->env);
	d->env = copy_env(tmp, d->c_env, 1);
	d->env[d->c_env] = ft_strdup(str);
	d->env[d->c_env + 1] = NULL;
	d->c_env++;
	free_list(d, tmp);
}

void	replace(t_mini *d, int i, int len, int a)
{
	char *tmp;
	
	(void)len;	
	ft_printf("Before %s\n", d->env[i]);
	tmp = d->env[i];
	free(d->env[i]);
	d->env[i] = ft_strdup(d->args[a]);
	ft_strlcpy(d->env[i], d->args[a], ft_strlen(d->args[a]) + 1);
	ft_printf("After %s\n", d->env[i]);
}

int		**export(t_mini *d)
{
	int		a;
	int		i;
	int		len;
	
	a = 1;
	ft_printf("After3 %s\n", d->env[17]);
	if (!d->args[1])
		return (env_alpha(d));
	while (d->args[a])
	{
		len = 0;
		while (d->args[a][len] != '\0')
		{
			if (d->args[a][len] == '=')
				break ;
			len++;
		}
		i = 0;
		while (i < d->c_env)
		{
			if (ft_strncmp(d->env[i], d->args[a], len) == 0 && d->env[i][len] == '=')
			{
				replace(d, i, len, a);
				break ;
			}
			i++;
		}
		a++;
	}
	// ft_printf("After2 %s\n", d->env[i]);
	return (NULL);
}
