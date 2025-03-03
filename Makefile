# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 16:34:42 by oohnivch          #+#    #+#              #
#    Updated: 2025/03/03 19:43:07 by oohnivch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#									Variables								   #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MFLAGS = --no-print-directory -C
HEADER = -I./includes
NAME = minishell

LIBDIR = ./libft
LIB = $(LIBDIR)/libft.a
LINKFLAG = -lreadline

NORMAL = \033[0m
GREEN = \033[1;32m
PURPLE = \033[1;35m
RED = \033[0;31m
YELLOW = \033[0;33m

# **************************************************************************** #
#									Source Files							   #
# **************************************************************************** #

SRC_PATH = src/
OBJ_PATH = obj/

SRC = main.c \
	  argv.c \
	  builtin_utils.c \
	  cd.c \
	  cd_utils.c \
	  clean.c \
	  cmd_path.c \
	  echo.c \
	  env.c \
	  no_env.c \
	  env_utils.c \
	  exec_init.c \
	  exec_init_utils.c \
	  exec_utils.c \
	  execution.c \
	  error.c \
	  general_utils.c \
	  here_doc.c \
	  here_doc_utils.c \
	  lexer.c \
	  lexer_create_tokens.c \
	  lexer_process_words.c \
	  lexer_set_token_types.c \
	  lexer_create_segment.c \
	  lexer_process_operators.c \
	  lexer_process_redirections.c \
	  parser.c \
	  parser_split_tokens.c \
	  parser_replace_split_token.c \
	  parser_expander.c \
	  parser_expansion_cases.c \
	  parser_utils.c \
	  pid.c \
	  syntax_checker.c \
	  syntax_checker_utils.c \
	  lexer_parser_free_utils.c \
	  path.c \
	  reroute.c \
	  reroute_utils.c \
	  free.c \
	  pwd.c \
	  signal.c \
	  exit.c \
	  export.c \
	  export_utils.c \
	  unset.c \
	  debug_utils.c \
	  debug_utils2.c \

OBJ = $(SRC:%.c=%.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

# **************************************************************************** #
#									Rules									   #
# **************************************************************************** #

all: $(OBJ_PATH) $(NAME)


$(NAME): $(OBJS) $(LIB) | logo
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME) $(LINKFLAG)
	@echo "\n$(GREEN)******** $(NAME) Created! ********$(NORMAL)\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(LIB)
	@if ! $(CC) $(CFLAGS) -o $@ -c $< $(HEADER) 2> error.txt; then\
		echo "$(RED)!!!!!!!! ERROR !!!!!!!!$(NORMAL)"; \
		echo "$(YELLOW)Error caused by $<$(NORMAL)\n"; \
		sed '$$d' error.txt; \
		echo "\n$(RED)Aborting makefile........$(NORMAL)"; \
		exit 1; \
	fi

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(LIB):
	@make $(MFLAGS) $(LIBDIR) all

clean:
	@make $(MFLAGS) $(LIBDIR) clean
	@rm -rf $(OBJ_PATH)
	@rm -f error.txt
	@echo "$(YELLOW)Deleting $(words $(OBJ)) object file(s) $(NORMAL)"
	@echo "$(GREEN)Deletion success! $(NORMAL)"

fclean:
	@make $(MFLAGS) $(LIBDIR) fclean
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME) $(BONUS) error.txt
	@echo "$(YELLOW)Deleting $(NAME) and $(words $(OBJ)) object file(s) $(NORMAL)" 
	@echo "$(GREEN)Deletion success! $(NORMAL)"

re: fclean all

logo:
	@echo "\n$(RED)▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖▗▖ ▗▖▗▄▄▄▖▗▖   ▗▖   "
	@echo "▐▛▚▞▜▌  █  ▐▛▚▖▐▌  █  ▐▌ ▐▌▐▌   ▐▌   ▐▌   "
	@echo "▐▌  ▐▌  █  ▐▌ ▝▜▌  █  ▐▛▀▜▌▐▛▀▀▘▐▌   ▐▌   "
	@echo "▐▌  ▐▌▗▄█▄▖▐▌  ▐▌▗▄█▄▖▐▌ ▐▌▐▙▄▄▖▐▙▄▄▖▐▙▄▄▖$(NORMAL)\n"

leak: all
	valgrind -s --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./$(NAME)

.PHONY: all leak clean fclean re logo
