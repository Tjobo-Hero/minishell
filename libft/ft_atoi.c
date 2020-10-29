/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:18:01 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/29 10:18:03 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static long int	ft_convert(const char *str, int i,
unsigned long int result, int sign)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((result >= 922337203685477580 && (str[i] - '0') > 7) && sign == 1)
			return (-1);
		else if ((result >= 922337203685477580 && (str[i] - '0') > 8)
		&& sign == -1)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int				ft_atoi(const char *str)
{
	unsigned long int	result;
	int					i;
	int					sign;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] != '\0' && (str[i] == ' ' || (8 < str[i] && str[i] < 14)))
		i++;
	if ((str[i] == '+' && str[i + 1] == '-') ||
	(str[i] == '-' && str[i + 1] == '+'))
		return (0);
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
		if (str[i] == '+')
			return (0);
	}
	result = ft_convert(str, i, result, sign);
	return ((int)result * sign);
}
