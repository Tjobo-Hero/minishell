# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rbraaksm <rbraaksm@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/29 10:22:31 by rbraaksm      #+#    #+#                  #
#    Updated: 2020/10/29 10:22:32 by rbraaksm      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = 	ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memalloc.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isalpha_str.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr.c \

BONUS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c \

LIB	  =	$(subst .c,.o, $(SRC))
BLIB  = $(subst .c,.o, $(BONUS))

all: $(NAME)

$(NAME):
	@gcc -c -Wall -Werror -Wextra $(SRC)
	@ar rc $(NAME) $(LIB)

bonus:
	@gcc -c -Wall -Werror -Wextra $(BONUS)
	@ar rc $(NAME) $(BLIB)

clean:
	/bin/rm -f $(LIB) $(BLIB)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
