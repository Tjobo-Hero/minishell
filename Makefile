# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tvan-cit <tvan-cit@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/06/04 13:57:07 by tvan-cit      #+#    #+#                  #
#    Updated: 2020/06/05 16:08:22 by tvan-cit      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# COLORS #

# This is a minimal set of ANSI/VT100 color codes
_END			=	\x1b[0m
_BOLD			=	\x1b[1m
_UNDER			=	\x1b[4m
_REV			=	\x1b[7m

# Colors
_GREY			=	\x1b[30m
_RED			=	\x1b[31m
_GREEN			=	\x1b[32m
_YELLOW			=	\x1b[33m
_BLUE			=	\x1b[34m
_PURPLE			=	\x1b[35m
_CYAN			=	\x1b[36m
_WHITE			=	\x1b[37m

# Inverted, i.e. colored backgrounds
_IGREY			=	\x1b[40m
_IRED			=	\x1b[41m
_IGREEN			=	\x1b[42m
_IYELLOW		=	\x1b[43m
_IBLUE			=	\x1b[44m
_IPURPLE		=	\x1b[45m
_ICYAN			=	\x1b[46m
_IWHITE			=	\x1b[47m

### COMPILING ###

SRC				=	main.c \
					get_next_line.c \
					get_next_line_utils.c \
					ft_split.c \
					ft_putstr.c \

OBJS			= $(subst .c,.o, $(SRC))

FLAGS			= -Wall -Werror -Wextra # -pedantic -std=c89
NAME			= minishell

RM 				= rm -rf

all:			$(NAME)

$(NAME):		$(OBJS)
				@gcc $(FLAGS) -o $(NAME) $(OBJS)
				@echo \
				"🍾🥂$(_BOLD) $(_GREEN)ALL FILES COMPILED$(_END)🥂🍾"

clean:
				@$(RM) $(OBJS)
				@echo "$(_YELLOW)'"$(OBJS)"' DELETED $(_END)❌"

fclean:			clean
				@$(RM) $(NAME)
				@echo "$(_YELLOW)'"$(NAME)"' DELETED $(_END)💔"

re:				fclean $(NAME)

