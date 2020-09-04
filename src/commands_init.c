/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands_init.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 16:46:22 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/09/03 13:51:27 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_on_off(t_mini *d, char c)
{
	if (c == '\'' && d->singleq)
		d->singleq = 0;
	else if (c == '\'')
		d->singleq = 1;
	else if (c == '\"' && d->doubleq)
		d->doubleq = 0;
	else if (c == '\"')
		d->doubleq = 1;
	if (d->singleq || d->doubleq)
		d->set = 1;
	else
		d->set = 0;
}
