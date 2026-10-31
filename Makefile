NAME = push_swap

CC 			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

LIBFT_DIR 	= libft
LIBFT 		= $(LIBFT_DIR)/libft.a

SRCS 		= main.c \
			  stack.c \
			  push.c \
			  swap.c \
			  rotate.c \
			  reverse_rotate.c \
			  bubble_algorithm.c \
			  chunck_algorithm.c \
			  radix_sort_algorithm.c \
			  compute_disorder.c\
			  adaptative_algorithm.c \

OBJ_DIR 	= obj
OBJS 		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: libft $(NAME)

# Compila primero la libft con su propio Makefile
libft:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c push_swap.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all libft clean fclean re
