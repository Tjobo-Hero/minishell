/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   upgrade_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:14:08 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 13:12:15 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	fill_char(t_arg *arg, char c, int *count)
{
	if (c == ' ' && arg->set == 0)
	{
		count[arg->c_i] = arg->c + 1;
		arg->c_i++;
	}
	arg->c++;
	arg->i++;
	return (c);
}

static void	fill_char_quote(t_arg *arg, char *in, char *out, int *count)
{
	arg->set = 1;
	out[arg->c] = fill_char(arg, in[arg->i], count);
	if (in[arg->i - 1] == '\"')
	{
		while (in[arg->i] != '\0')
		{
			if (in[arg->i] == '\"')
				break ;
			if (in[arg->i] == '\\')
			{
				out[arg->c] = fill_char(arg, in[arg->i], count);
				out[arg->c] = fill_char(arg, in[arg->i], count);
			}
			else
				out[arg->c] = fill_char(arg, in[arg->i], count);
		}
		arg->set = 0;
		out[arg->c] = fill_char(arg, in[arg->i], count);
		return ;
	}
	while (in[arg->i] != '\'' && in[arg->i] != '\0')
		out[arg->c] = fill_char(arg, in[arg->i], count);
	arg->set = 0;
	out[arg->c] = fill_char(arg, in[arg->i], count);
}

static void	fill_redirection(t_arg *arg, char *in, char *out, int *count)
{
	char	c;

	c = in[arg->i];
	if (c == '|' && arg->set == 0)
	{
		arg->count[arg->a] = (in[arg->i - 1] == ' ' ? arg->c_i : arg->c_i + 1);
		arg->a++;
	}
	if (c == '|' && arg->set == 1)
	{
		out[arg->c] = fill_char(arg, in[arg->i], count);
		arg->set = 0;
	}
	else if (arg->i > 0 && in[arg->i - 1] != ' ' && arg->i != 0)
	{
		out[arg->c] = fill_char(arg, ' ', count);
		arg->i--;
	}
	while (in[arg->i] == c)
		out[arg->c] = fill_char(arg, in[arg->i], count);
	if (in[arg->i] != ' ')
	{
		out[arg->c] = fill_char(arg, ' ', count);
		arg->i--;
	}
}

static void	spaces(t_arg *arg, char *in)
{
	while (in[arg->i] == ' ')
		arg->i++;
	arg->i--;
}

void		upgrade_line(t_arg *arg, char *in, char *out, int *count)
{
	while (in[arg->i] == ' ')
		arg->i++;
	while (arg->i < (int)ft_strlen(in) && in[arg->i] != '\0')
	{
		if (in[arg->i] == '\\' && arg->set == 0)
		{
			out[arg->c] = fill_char(arg, in[arg->i], count);
			arg->set = 1;
			out[arg->c] = fill_char(arg, in[arg->i], count);
			arg->set = 0;
		}
		if (in[arg->i] == '\"' || in[arg->i] == '\'')
			fill_char_quote(arg, in, out, count);
		else if (in[arg->i] == '<' || in[arg->i] == '>' || in[arg->i] == '|')
			fill_redirection(arg, in, out, count);
		else if (in[arg->i] == '\n')
			arg->i++;
		else
			out[arg->c] = fill_char(arg, in[arg->i], count);
		if (arg->i < (int)ft_strlen(in) && in[arg->i] == ' ')
			spaces(arg, in);
	}
	if (in[arg->i - 1] != ' ' && in[arg->i - 1] != ' ')
		count[arg->c_i] = arg->c + 1;
	arg->count[arg->a] = arg->c_i + 1;
}
