NAME        = libftprintferror.a

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

COMMON      = ft_printf_error.c ft_printf_utils.c
SRCS        = $(COMMON) ft_printf_format.c

LIBFT_DIR   = ../libft
# Mantenemos las cabeceras para que pueda compilar buscando los tipos de la libft
HEADERS     = ft_printf_error.h $(LIBFT_DIR)/libft.h

OBJ_DIR     = obj
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

# CORRECCIÓN: La librería solo se compone de sus propios objetos (.o)
# No copiamos la libft aquí para evitar la duplicación de funciones en push_swap
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	@echo "✨ $(NAME) creada con éxito."

# Compilamos los objetos buscando las cabeceras de la libft si fuera necesario
$(OBJ_DIR)/%.o: %.c $(HEADERS) Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I. -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# El Makefile de esta sub-librería NO debe limpiar la libft,
# de eso ya se encarga el Makefile principal de push_swap.
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
