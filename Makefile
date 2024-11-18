# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oohnivch <@student.42vienna.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 10:24:00 by oohnivch          #+#    #+#              #
#    Updated: 2024/11/18 10:31:39 by oohnivch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#									Variables								   #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
MFLAGS = --no-print-directory -C
HEADER = -I./includes
# HEADER_BONUS = -I./includes_bonus/
NAME = minishell
# BONUS = pipex_bonus

LIBDIR = ./libft
LIB = $(LIBDIR)/libft.a

NORMAL = \033[0m
GREEN = \033[1;32m
PURPLE = \033[1;35m
RED = \033[0;31m
YELLOW = \033[0;33m

# **************************************************************************** #
#									Source Files							   #
# **************************************************************************** #

SRC_PATH = src/
# SRC_PATH_BONUS = src_bonus/
OBJ_PATH = obj/
# OBJ_PATH_BONUS = obj_bonus/

SRC = main.c \
	  argv.c \
	  cd.c \
	  clean.c \
	  cmd_path.c \
	  constructors.c \
	  echo.c \
	  env.c \
	  env_utils.c \
	  exec_utils.c \
	  execution.c \
	  general_utils.c \
	  here_doc.c \
	  lexer.c \
	  lexer_check_quotes.c \
	  lexer_init_tokens.c \
	  lexer_token_expand.c \
	  lexer_token_linking.c \
	  lexer_word_processing.c \
	  parser.c \
	  parser_utils1.c \
	  parser_utils2.c \
	  path.c \
	  reroute.c \
	  signal.c \
	  syntax_check.c

# SRC_BONUS = main_bonus.c annihilate_bonus.c extract_bonus.c access_bonus.c \
			# general_utils_bonus.c process_bonus.c reroute_bonus.c here_doc_bonus.c

OBJ = $(SRC:%.c=%.o)
# OBJ_BONUS = $(SRC_BONUS:%.c=%.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))
# OBJS_BONUS = $(addprefix $(OBJ_PATH_BONUS), $(OBJ_BONUS))

# **************************************************************************** #
#									Rules									   #
# **************************************************************************** #

all: $(OBJ_PATH) $(NAME)

# bonus: $(OBJ_PATH_BONUS) $(BONUS)

# $(NAME): $(OBJS) $(LIB) | bernhard
$(NAME): $(OBJS) $(LIB) | logo
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME) 
	@echo "\n$(GREEN)******** $(NAME) Created! ********$(NORMAL)\n"

# $(BONUS): $(OBJS_BONUS) $(LIB)
# 	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIB) -o $(BONUS) 
# 	@echo "\n$(PURPLE)******** $(BONUS) Created! ********$(NORMAL)\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(LIB)
	@if ! $(CC) $(CFLAGS) -o $@ -c $< $(HEADER) 2> error.txt; then\
		echo "$(RED)!!!!!!!! ERROR !!!!!!!!$(NORMAL)"; \
		echo "$(YELLOW)Error caused by $<$(NORMAL)\n"; \
		sed '$$d' error.txt; \
		echo "\n$(RED)Aborting makefile........$(NORMAL)"; \
		exit 1; \
	fi

# $(OBJ_PATH_BONUS)%.o: $(SRC_PATH_BONUS)%.c $(LIB)
# 	@if ! $(CC) $(CFLAGS) -o $@ -c $< $(HEADER_BONUS) 2> error.txt; then\
#  		echo "$(RED)!!!!!!!! ERROR !!!!!!!!$(NORMAL)"; \
#  		echo "$(YELLOW)Error caused by $<$(NORMAL)\n"; \
#  		sed '$$d' error.txt; \
#  		echo "\n$(RED)Aborting makefile........$(NORMAL)"; \
#  		exit 1; \
#  	fi

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

# $(OBJ_PATH_BONUS):
# 	@mkdir $(OBJ_PATH_BONUS)

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

rebonus: fclean bonus

.PHONY: all bonus clean fclean re rebonus bernhard logo
