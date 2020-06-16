# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rbraaksm <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/30 13:04:08 by rbraaksm       #+#    #+#                 #
#    Updated: 2020/01/08 13:22:17 by rbraaksm      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS =	ft_printf.c \
		ft_fill_flags.c \
		ft_printf_utils.c \
		ft_character.c \
		ft_string.c \
		ft_pointer.c \
		ft_string_utils.c \
		ft_digit.c \
		ft_digit_utils.c \
		ft_unsigned.c \
		ft_hexa.c \
		ft_percentage.c \
		ft_flag_n.c \

LIB = $(SRCS:%.c=%.o)

BONUS = ft_printf_bonus.c \
		ft_fill_flags_bonus.c \
		ft_printf_utils_bonus.c \
		ft_character_bonus.c \
		ft_string_bonus.c \
		ft_pointer_bonus.c \
		ft_string_utils_bonus.c \
		ft_digit_bonus.c \
		ft_digit_utils_bonus.c \
		ft_unsigned_bonus.c \
		ft_hexa_bonus.c \
		ft_percentage_bonus.c \
		ft_flag_n_bonus.c \

BLIB = $(BONUS:%.c=%.o)

all: $(NAME)

$(NAME):
	gcc -c -Wall -Wextra -Werror $(SRCS)
	ar rc $(NAME) $(LIB)

bonus:
	gcc -c -Wall -Wextra -Werror $(SRCS) $(BONUS)
	ar rc $(NAME) $(BLIB)

clean:
	/bin/rm -f $(LIB) $(BLIB)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
