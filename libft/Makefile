# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/08 13:40:55 by oohnivch          #+#    #+#              #
#    Updated: 2025/01/21 12:34:59 by oohnivch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#									Variables								   #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
HEADER = -I.
NAME = libft.a
AR = ar rcs

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

CSRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	   ft_isprint.c ft_toupper.c ft_tolower.c ft_isspace.c

SSRC = ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c \
	   ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_atoi.c \
	   ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
	   ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c

MSRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	   ft_memchr.c ft_memcmp.c ft_calloc.c

FSRC = ft_putnbr_fd.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c 

BSRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	   ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	   ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

PSRC = ft_printf.c ft_putchar.c ft_putnbr.c ft_putstr.c \
	   ft_puthex.c ft_putptr.c ft_putuint.c ft_printerr.c

GSRC = get_next_line.c get_next_line_2.c get_next_line_utils.c

SRC =  $(CSRC) $(SSRC) $(MSRC) $(FSRC) $(PSRC) $(GSRC) $(BSRC)
OBJ =  $(SRC:%.c=%.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

# **************************************************************************** #
#									Rules									   #
# **************************************************************************** #

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $(OBJS)
	@echo "\n$(PURPLE)******** $(NAME) Created! ********$(NORMAL)\n"

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@if ! $(CC) $(CFLAGS) -c $< -o $@ $(HEADER) 2> error.txt; then\
		echo "$(RED)!!!!!!!! ERROR !!!!!!!!$(NORMAL)"; \
		echo "$(YELLOW)Error caused by $<$(NORMAL)\n"; \
		sed '$$d' error.txt; \
		echo "\n$(RED)Aborting makefile........$(NORMAL)"; \
		exit 1; \
	fi

bonus: $(OBJ_PATH) $(NAME)

clean:
	@rm -rf $(OBJ_PATH)
	@rm -f error.txt
	@echo "$(YELLOW)Deleting $(words $(OBJ)) object file(s) $(NORMAL)"
	@echo "$(GREEN)Deletion success! $(NORMAL)"

fclean: 
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME) error.txt
	@echo "$(YELLOW)Deleting $(NAME) and $(words $(OBJ)) object file(s) $(NORMAL)" 
	@echo "$(GREEN)Deletion success! $(NORMAL)"

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus
