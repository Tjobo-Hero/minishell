/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tvan-cit <tvan-cit@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 14:19:31 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/07/01 11:41:45 by rbraaksm      ########   odam.nl         */
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
	if (tmp == NULL)
		return (char_malloc_error());
	while (i < x)
	{
		tmp[i] = ft_strdup(str[i]);
		if (tmp[i] == NULL)
			return (char_malloc_error());
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

	(void)d;
	i = 0;
	while (tmp[i])
		i++;
	while (i > 0)
	{
		free(tmp[i - 1]);
		i--;
	}
	free(tmp);
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
			is_count = 0;
		while (tmp[i][k])
		{
			write(1, &tmp[i][k], 1);
			if (tmp[i][k] == '=' && is_count == 0)
			{
				write(1, "\"", 1);
				is_count = 1;
			}
			k++;
		}
		if (is_count)
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
	free_list(d, d->env);
	d->env = copy_env(tmp, d->c_env, 1);
	d->env[d->c_env] = ft_strdup(str);
	d->env[d->c_env + 1] = NULL;
	d->c_env++;
	free_list(d, tmp);
}

int	replace(t_mini *d, int i, int a, int len)
{
	char *tmp;
	
	ft_printf("test\n");
	if (d->env[i][len] == '=' && d->args[a][len] == '\0')
		return (0);
	ft_printf("env : %s\n", d->env[i]);
	ft_printf("arg : %s\n", d->args[a]);
	(void)len;
	tmp = d->env[i];
	free(d->env[i]);
	d->env[i] = ft_strdup(d->args[a]);
	ft_strlcpy(d->env[i], d->args[a], ft_strlen(d->args[a]) +1);
	return (0);
}

int		check_cmp(t_mini *d, int a)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (d->args[a][len] != '\0')
	{
		if (d->args[a][len] == '=')
			break;
		len++;
	}
	ft_printf("Len : %d\n", len);
	while (i < d->c_env)
	{
		if (ft_strncmp(d->env[i], d->args[a], len) == 0 && d->env[i][len] == '=')
			return (replace(d, i, a, len));
		// if (ft_strncmp(d->env[i], d->args[a], len) == 0 && d->env[i][len] == '\0')
		// 	return (replace(d, i, a, len));	
		i++;
	}
	return (1);
}

int		**export(t_mini *d)
{
	int		a;
	
	a = 1;
	if (!d->args[1])
		return (env_alpha(d));
	while (d->args[a])
	{
		if (check_cmp(d, a) == 1)
			new_list(d, d->args[a]);
		a++;
	}
	return (NULL);
}
