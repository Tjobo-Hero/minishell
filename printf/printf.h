/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: renebraaksma <renebraaksma@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 10:16:13 by rbraaksm      #+#    #+#                 */
/*   Updated: 2020/10/14 12:36:53 by tvan-cit      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdlib.h>

typedef struct	s_flags
{
	char		type;
	int			min;
	int			zero;
	int			dot;
	int			asterisk;
	int			width;
	int			prec;
	int			hash;
	int			space;
	int			plus;
	int			l;
	int			ll;
	int			h;
	int			hh;
	int			index;
	int			neg;
	int			check;
	char		*str;
}				t_flags;

int				ft_printf(const char *str, ...);
void			ft_empty_flags(t_flags *flags);
int				ft_flag_type(const char *str, t_flags *flags);
void			ft_fill_flags(const char *str, t_flags *flags, va_list args);
void			ft_find_width_and_prec(const char *str, t_flags *flags,
				va_list args);
void			ft_fill_extra_flags(const char *str, t_flags *flags);
int				ft_atoi(const char *str);
int				ft_putchar(char c);
int				ft_putstring(char *s);
/* int				ft_strlen(char *s); */
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_number_length(size_t nbr, int base);
size_t			ft_putnbr(size_t nbr, int len, t_flags *flags);
int				ft_character(va_list args, t_flags *flags);
int				ft_string(va_list args, t_flags *flags);
int				ft_pointer(va_list args, t_flags *flags);
int				ft_pointer_basic(t_flags *flags, long nbr, int len, int count);
int				ft_digit(va_list args, t_flags *flags);
int				ft_digit_minus_zero(t_flags *flags, size_t nbr, int len,
				int count);
int				ft_digit_minus_plus(t_flags *flags, size_t nbr, int len,
				int count);
int				ft_digit_prec(t_flags *flags, size_t nbr, int len, int count);
int				ft_calc_width(t_flags *flags, int len, int nbr);
int				ft_unsigned(va_list args, t_flags *flags);
int				ft_unsigned_prec(t_flags *flags, size_t nbr, int len,
				int count);
int				ft_hexa(va_list args, t_flags *flags);
int				ft_hexa_prec(t_flags *flags, size_t nbr, int len, int count);
int				ft_percentage(va_list args, t_flags *flags);
int				ft_flag_n(va_list args, t_flags *flags, int count);
#endif
