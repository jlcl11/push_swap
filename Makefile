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

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

SRCS = main.c flags.c parse.c parse_utils.c stack.c algorithm.c push.c swap.c rotate.c reverse_rotate.c

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

$(OBJ_DIR)/%.o: %.c push_swap.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

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
