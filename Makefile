# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rbraaksm <rbraaksm@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/29 10:08:12 by rbraaksm      #+#    #+#                  #
#    Updated: 2020/10/29 13:15:01 by rbraaksm      ########   odam.nl          #
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
FLAGS			= -Wall -Werror -Wextra  #-g -fsanitize=address

SRC_DIR			= ./src/
OBJ_DIR			= ./obj/
INCLUDE_DIR		= ./include/


SRC_FILES		=	minishell \
					environ\
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
					cmd_exit \
					utils \
					utils2 \
					utils3 \
					update_array \
					commands \
					cmd_export_utils1 \
					cmd_export_utils2 \
					upgrade_line \
					pipes \
					redirections \
					commands_init \
					remove \
					syntax_check \
					utils_table \
					utils_table_alpha \
					utils_table_set \
					return_values \

INCLUDE_DIR 	:= $(INCLUDE_DIR:%=-I%)
SRC_FILES 		:= $(SRC_FILES:%=%.o)
OBJ_FILES 		:= $(SRC_FILES:%=$(OBJ_DIR)%)

OBJS			= $(subst .c,.o, $(SRC))

all: $(NAME)

$(NAME):		$(OBJ_FILES)
				@cd libft && $(MAKE);
				@cp libft/libft.a .
				@echo "$(_BOLD) $(_PURPLE)BUILDING '"$(NAME)"' $(_END)"
				@$(CC)	$^ \
				-o $(NAME) \
				$(FLAGS) \
				libft.a \
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
				@cd libft && rm -f *.o
				@echo "$(_YELLOW)'"$(NAME)"' DELETED $(_END)💔"

re:				fclean $(NAME)

.PHONY:			all re clean fclean
