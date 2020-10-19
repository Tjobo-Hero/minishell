/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_echo.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/04 10:28:24 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/19 15:30:18 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		dollar_sign(t_mini *d, char *arg)
{
	char	*look;
	int		i;
	t_env	*tmp;

	i = 1;
	while (arg[i] != '\0' && ft_isalnum(arg[i]))
		i++;
	look = malloc(sizeof(char*) * (i + 1));
	look == NULL ? error_malloc(d, NULL, NULL, NULL) : 0;
	ft_strlcpy(look, &arg[1], i);
	tmp = look_up(look, d->echo);
	if (arg[1] == '?')
	{
		i++;
		ft_putnbr_fd(d->ret, d->fd);
		if (arg[2] != ' ')
			ft_putstr_fd(&arg[2], d->fd);
	}
	else if (tmp != NULL)
		ft_putstr_fd(tmp->echo, d->fd);
	free(look);
	return (i);
}

static int	write_double(t_mini *d, char *arg, int i)
{
	int		set;

	set = 0;
	i++;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\\' && set == 0)
		{
			set = 1;
			i++;
		}
		else if (arg[i] == '$' && set == 0)
			i += dollar_sign(d, &arg[i]);
		else
		{
			if (!write(d->fd, &arg[i], 1))
				error_malloc(d, NULL, NULL, NULL);
			i++;
			set = 0;
		}
		if (arg[i] == '\"' && set == 0)
			break ;
	}
	i++;
	return (i);
}

static int	write_single(t_mini *d, char *arg, int i)
{
	i++;
	while (arg[i] != '\'')
	{
		if (!write(d->fd, &arg[i], 1))
			error_malloc(d, NULL, NULL, NULL);
		i++;
	}
	i++;
	return (i);
}

void	write_arg(t_mini *d, int a)
{
	int	i;
	int	set;

	i = 0;
	set = 0;
	while (d->orig[a][i] != '\0')
	{
		if (d->orig[a][i] == '\\' && set == 0)
		{
			set = 1;
			i++;
		}
		else if (d->orig[a][i] == '\'' && set == 0)
			i = write_single(d, d->orig[a], i);
		else if (d->orig[a][i] == '\"' && set == 0)
			i = write_double(d, d->orig[a], i);
		else if (d->orig[a][i] == '$' && set == 0)
			i += dollar_sign(d, &d->orig[a][i]);
		else
		{
			i += write(d->fd, &d->orig[a][i], 1);
			set = 0;
		}
	}
}

int		**echo(t_mini *d)
{
	int	a;

	a = 1;
	if (!d->args[1])
	{
		ft_putchar_fd('\n', d->fd);
		return (0);
	}
	if (ft_strncmp(d->args[a], "-n", 2) == 0)
		a++;
	while (d->args[a])
	{
		write_arg(d, a);
		a++;
		if (d->args[a])
			ft_putchar_fd(' ', d->fd);
	}
	if ((d->args[1] && ft_strncmp(d->args[1], "-n", 3) != 0))
		ft_putchar_fd('\n', d->fd);
	return (0);
}
