/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 14:19:31 by tvan-cit      #+#    #+#                 */
/*   Updated: 2020/07/09 18:30:03 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char		**copy_env(char **str, int x, int c)
// {
// 	char	**tmp;
// 	int		i;

// 	i = 0;
// 	if (c == 1)
// 		tmp = (char **)malloc(sizeof(char *) * (x + 2));
// 	else
// 		tmp = (char **)malloc(sizeof(char *) * (x + 1));
// 	if (tmp == NULL)
// 		return (char_malloc_error());
// 	while (i < x)
// 	{
// 		tmp[i] = ft_strdup(str[i]);
// 		if (tmp[i] == NULL)
// 			return (char_malloc_error());
// 		i++;
// 	}
// 	if (c == 1)
// 		return (tmp);
// 	tmp[i] = NULL;
// 	return (tmp);
// }

// void	free_list(t_mini *d, char **tmp)
// {
// 	int		i;

// 	(void)d;
// 	i = 0;
// 	while (tmp[i])
// 		i++;
// 	while (i > 0)
// 	{
// 		free(tmp[i - 1]);
// 		i--;
// 	}
// 	free(tmp);
// }

void	print_export(t_env **export)
{
	int i;

	i = 0;
	while (export[i] != NULL)
	{
		ft_printf("declare -x %s", export[i]->head);
		if (export[i]->set)
			write(1, "=\"", 2);
		ft_printf("%s", export[i]->echo);
		if (export[i]->set)
			write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
}

void	swap(t_mini *d, int i)
{
	t_env *tmp;

	tmp = d->export[i];
	d->export[i] = d->export[i + 1];
	d->export[i + 1] = tmp;
}

int		**env_alpha(t_mini *d)
{
	int i;

	i = 0;
	d->export = d->env;
	while (d->export[i + 1] != NULL)
	{
		while (ft_strncmp(d->export[i]->head, d->export[i + 1]->head,
				ft_strlen(d->export[i]->head)) > 0)
		{
			swap(d, i);
			i = 0;
		}
		i++;
	}
	print_export(d->export);
	return (0);
}

// void	new_list(t_mini *d, char *str)
// {
// 	char	**tmp;

// 	if (str[0] < 65 || (str[0] > 90 && str[0] < 95) ||
// 		(str[0] > 95 && str[0] < 97) || str[0] > 122)
// 		return ;
// 	tmp = copy_env(d->env, d->c_env, 0);
// 	free_list(d, d->env);
// 	d->env = copy_env(tmp, d->c_env, 1);
// 	// d->env[d->c_env] = check_for_doubleq(str);
// 	d->env[d->c_env] = ft_strdup(str);
// 	d->env[d->c_env + 1] = NULL;
// 	d->c_env++;
// 	free_list(d, tmp);
// }

void			hash_table_insert_index1(t_env *user, t_env **env, int index)
{
		printf("%s\n", user->head);

	if (user == NULL)
		return ;
	user->next = env[index];
	env[index] = user;
	return ;
}

void	new_list(t_mini *d, char *arg)
{
	t_env	tmp[1];
	int i;

	i = 0;
	if (arg[0] < 65 || (arg[0] > 90 && arg[0] < 95) ||
		(arg[0] > 95 && arg[0] < 97) || arg[0] > 122)
		return ;
	while (d->env[i] != NULL)
		i++;
	// print_env(d->env);
	// printf("%d\n", i);
	set_env(&tmp[0], arg, 0);
	printf("%s\n", tmp->head);
	printf("%s\n", tmp->list);
	printf("%s\n", tmp->echo);
	printf("%zu\n", ft_strlen(tmp->head));
	int z = 0;
	while (z < 4)
	{
		// d->env[i]->head = 'P';
		z++;
	}
	printf("%s\n", d->env[i]->head);
	// ft_strlcpy(d->env[i]->head, tmp[0].head, ft_strlen(tmp->head) + 1);
	// ft_strlcpy(d->env[i]->list, &tmp->list, ft_strlen(tmp->list));
	// ft_strlcpy(d->env[i]->echo, &tmp->echo, ft_strlen(tmp->echo));
	// hash_table_insert_index1(&tmp[0], d->env, i);
}

// int		replace(t_mini *d, int i, int a, int len)
// {
// 	char *tmp;

// 	if (d->args[a][len] == '\0')
// 		return (0);
// 	tmp = d->env[i];
// 	free(d->env[i]);
// 	d->env[i] = ft_strdup(d->args[a]);
// 	ft_strlcpy(d->env[i], d->args[a], ft_strlen(d->args[a]) + 1);
// 	return (0);
// }

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
	int i;
	int len;

	len = 0;
	i = 0;
	tmp = NULL;
	tmp = look_up(d->args[a], d->env);
	if (tmp == NULL)
		return (1);
	printf("test\n");
	while (d->args[a][len] != '=' && d->args[a][len] != '\0')
		len++;
	while (ft_strncmp(d->args[a], d->env[i]->head, ft_strlen(d->env[i]->head)) != 0)
		i++;
	if (d->env[i]->set == 1)
		return (replace(d, d->env[i], a, len));
	else
		return (replace(d, d->env[i], a, len));
//if (d->env[i]->head[len] == '\0' && d->args[a][len] == '=')
}

int		**export(t_mini *d)
{
	int	a;

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
