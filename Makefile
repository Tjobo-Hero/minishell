# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: renebraaksma <renebraaksma@student.42.f      +#+                      #
#                                                    +#+                       #
#    Created: 2020/06/04 13:57:07 by tvan-cit      #+#    #+#                  #
#    Updated: 2020/10/01 12:55:44 by rbraaksm      ########   odam.nl          #
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

NAME			= minishell
FLAGS			= -Wall -Werror -Wextra -g # -pedantic -std=c89

SRC_DIR			= ./src/
OBJ_DIR			= ./obj/
INCLUDE_DIR		= ./include/


SRC_FILES		=	minishell \
					environ_init \
					environ_utils \
					environ_utils1 \
					ft_free \
					get_next_line \
					commands_run \
					commands_check \
					commands_execute \
					cmd_pwd \
					cmd_cd \
					cmd_env \
					cmd_unset \
					cmd_export \
					cmd_echo \
					utils \
					commands \
					cmd_export_utils1 \
					cmd_export_utils2 \
					cmd_export_utils3 \
					commands_line \
					pipes \
					redirections \
					new_arg \
					commands_init \
					remove_case \
					syntax_check \
					# pipes_init \

INCLUDE_DIR 	:= $(INCLUDE_DIR:%=-I%)
SRC_FILES 		:= $(SRC_FILES:%=%.o)
OBJ_FILES 		:= $(SRC_FILES:%=$(OBJ_DIR)%)

OBJS			= $(subst .c,.o, $(SRC))

all: $(NAME)

$(NAME):		$(OBJ_FILES)
				@cd libft && $(MAKE);
				@cd printf && $(MAKE);
				@cp libft/libft.a .
				@cp printf/libftprintf.a .
				@echo "$(_BOLD) $(_PURPLE)BUILDING '"$(NAME)"' $(_END)"
				@$(CC)	$^ \
				-o $(NAME) \
				libft.a \
				libftprintf.a \
				# -I libft \
				# -L libft -lft

				@echo \
				"🍾🥂$(_BOLD) $(_GREEN)ALL FILES COMPILED$(_END)🥂🍾"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(INCLUDE_DIR) \
				-c $^ \
				-o $@ \
				$(FLAGS)
clean:
				@$(RM) -rf $(OBJ_DIR)
				@echo "$(_YELLOW)'"$(OBJ_FILES)"' DELETED $(_END)❌"

fclean:			clean
				@$(RM) -f $(NAME)
				@$(RM) -f *.a
				@$(RM) -f ./minishell*
				@cd libft && rm -f *.a
				@cd printf && rm -f *.a
				@cd libft && rm -f *.o
				@cd printf && rm -f *.o
				@echo "$(_YELLOW)'"$(NAME)"' DELETED $(_END)💔"

re:				fclean $(NAME)

.PHONY:			all re clean fclean
