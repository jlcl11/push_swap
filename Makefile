# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: jocorral <jocorral@student.42malaga.com>   +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2026/10/23 00:00:00 by jocorral          #+#    #+#             #
#   Updated: 2026/10/23 00:00:00 by jocorral         ###   ########.fr       #
#                                                                            #
# ************************************************************************** #

NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIB_DIR = lib

LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = $(LIB_DIR)/printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

HEADER = push_swap.h

SRC_DIR = ficheros

PARSING = flags.c parse.c parse_utils.c
STACK = stack.c debug.c
OPS = push.c swap.c rotate.c reverse_rotate.c
ALGOS = bubble_algorithm.c chunck_algorithm.c radix_sort_algorithm.c \
	compute_disorder.c adaptative_algorithm.c

SRCS = main.c \
	$(addprefix parseo/, $(PARSING)) \
	$(addprefix stack/, $(STACK)) \
	$(addprefix operaciones/, $(OPS)) \
	$(addprefix algoritmos/, $(ALGOS))

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: libft printf $(NAME)

# Compila primero la libft con su propio Makefile
libft:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

# Igual con la ft_printf
printf:
	@$(MAKE) --no-print-directory -C $(PRINTF_DIR)

$(PRINTF):
	@$(MAKE) --no-print-directory -C $(PRINTF_DIR)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF) $(LIBFT) -o $(NAME)

# mkdir -p crea también las subcarpetas de obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@$(MAKE) --no-print-directory -C $(PRINTF_DIR) clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@$(MAKE) --no-print-directory -C $(PRINTF_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all libft printf clean fclean re
