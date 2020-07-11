/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 14:19:31 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/07/11 09:32:26 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tmp(t_env **tmp)
{
	int i;
	unsigned int c;

	i = 0;
	c = 0;
	while (tmp[c] != NULL)
	{
		while (tmp[i]->index != c)
			i++;
		ft_printf("%s", tmp[i]->head);
		if (tmp[i]->set)
		{
			write(1, "=\"", 2);
			ft_printf("%s", tmp[i]->echo);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i = 0;
		c++;
	}
}

void	swap(t_env **tmp, int i, int n)
{
	int tmp1;

	tmp1 = tmp[i]->index;
	tmp[i]->index = tmp[n]->index;
	tmp[n]->index = tmp1;
}

int		**alpha(t_env **env)
{
	int i;
	int c;
	int n;
	int d;

	d = 0;
	while (env[d] != NULL)
	{
		i = d;
		n = i + 1;
		while (env[n] != NULL)
		{
			c = ft_strncmp(env[i]->head, env[n]->head, ft_strlen(env[i]->head));
			if ((c > 0 && env[i]->index < env[n]->index) ||
				(c < 0 && env[i]->index > env[n]->index))
			{
				swap(env, i, n);
				i = d;
				n = i + 1;
			}
			else
				n++;
		}
		d++;
	}
	print_tmp(env);
	return (0);
}

void	new_list(t_mini *d, char *arg)
{
	t_env	env_tmp[ENV_SIZE];
	t_env	echo_tmp[ENV_SIZE];
	int i;

	i = 0;
	if (arg[0] < 65 || (arg[0] > 90 && arg[0] < 95) ||
		(arg[0] > 95 && arg[0] < 97) || arg[0] > 122)
		return ;
	while (d->env[i] != NULL)
		i++;
	set_env(&env_tmp[i], arg, 0, i);
	set_env(&echo_tmp[i], arg, 1, 0);
	hash_table_insert_index(&env_tmp[i], d->env, i);
	hash_table_insert_index(&echo_tmp[i], d->echo, hash_echo(echo_tmp[i].head));
}

int		replace(t_mini *d, t_env *env, int a, int len)
{
	char *tmp;
	int	i;

	if (d->args[a][len] == '\0')
		return (0);
	i = ft_strlen(d->args[a]);
	env->set = 0;
	if (d->args[a][len] == '=')
		env->set = 1;
	tmp = env->head;
	clear_str(env->list);
	clear_str(env->echo);
	ft_strlcpy(env->list, d->args[a], i + 1);
	ft_strlcpy(env->echo, &d->args[a][len + 1], (i - len));
	return (0);
}

int		check_cmp(t_mini *d, int a)
{
	t_env	*tmp;
	char	*str;
	int i;
	int len;

	len = 0;
	i = 0;
	str = NULL;
	while (d->args[a][len] != '=' && d->args[a][len] != '\0')
		len++;
	if (d->args[a][len] == '=')
	{
		str = malloc(sizeof(char *) * len);
		ft_strlcpy(str, d->args[a], len + 1);
	}
	else
		str = ft_strdup(d->args[a]);
	tmp = look_up(str, d->echo);
	if (tmp == NULL)
		return (1);
	while (ft_strncmp(str, d->env[i]->head, ft_strlen(d->env[i]->head)) != 0)
		i++;
	free(str);
	if (d->env[i]->set == 1)
		return (replace(d, d->env[i], a, len));
	else
		return (replace(d, d->env[i], a, len));
}

int		**export(t_mini *d)
{
	int	a;

	a = 1;
	if (!d->args[1])
		return (alpha(d->env));
	while (d->args[a])
	{
		if (check_cmp(d, a) == 1)
			new_list(d, d->args[a]);
		a++;
	}
	return (NULL);
}
