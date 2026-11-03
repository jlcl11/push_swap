# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: jocorral <jocorral@student.42malaga.com>   +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2026/10/23 00:00:00 by jocorral          #+#    #+#             #
#   Updated: 2026/11/03 17:30:00 by jocorral         ###   ########.fr       #
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

PRINTF_ERROR_DIR = $(LIB_DIR)/printf_error
PRINTF_ERROR = $(PRINTF_ERROR_DIR)/libftprintferror.a

HEADER = push_swap.h

SRC_DIR = ficheros

PARSING = flags.c parse.c parse_utils.c
STACK = stack.c
OPS = push.c swap.c rotate.c reverse_rotate.c
ALGOS = selection_algorithm.c chunck_algorithm.c radix_sort_algorithm.c \
	compute_disorder.c adaptative_algorithm.c

SRCS = $(addprefix parseo/, $(PARSING)) \
	$(addprefix stack/, $(STACK)) \
	$(addprefix operaciones/, $(OPS)) \
	$(addprefix algoritmos/, $(ALGOS))

OBJ_DIR = obj
OBJS = $(OBJ_DIR)/main.o $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# El target 'all' solo debe depender del binario final para evitar relinkeo
all: $(NAME)

# REGLA PRINCIPAL: Ahora depende de los tres archivos .a reales y los objetos
$(NAME): $(OBJS) $(LIBFT) $(PRINTF) $(PRINTF_ERROR)
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF) $(LIBFT) $(PRINTF_ERROR) -o $(NAME)

# Reglas reales para los archivos binarios de las librerías
$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(PRINTF):
	@$(MAKE) --no-print-directory -C $(PRINTF_DIR)

$(PRINTF_ERROR):
	@$(MAKE) --no-print-directory -C $(PRINTF_ERROR_DIR)

# main.c está en la raíz, fuera de SRC_DIR
$(OBJ_DIR)/main.o: main.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I. -c $< -o $@

# Regla genérica para los objetos dentro de ficheros/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@$(MAKE) --no-print-directory -C $(PRINTF_DIR) clean
	@$(MAKE) --no-print-directory -C $(PRINTF_ERROR_DIR) clean
	$(RM) -r $(OBJ_DIR)


fclean: clean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@$(MAKE) --no-print-directory -C $(PRINTF_DIR) fclean
	@$(MAKE) --no-print-directory -C $(PRINTF_ERROR_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
