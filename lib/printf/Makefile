NAME	= libftprintf.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

COMMON	= ft_printf.c \
		  ft_printf_utils.c

SRCS	= $(COMMON) \
		  ft_printf_format.c

BONUS_SRCS	= $(COMMON) \
			  ft_printf_format_bonus.c \
			  ft_printf_conv_bonus.c \
			  ft_printf_nbr_bonus.c

LIBFT_DIR	= ../libft
LIBFT	= $(LIBFT_DIR)/libft.a
HEADERS	= ft_printf.h $(LIBFT_DIR)/libft.h

OBJ_DIR	= obj
OBJS	= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS	= $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:.c=.o))
BONUS_MARK	= $(OBJ_DIR)/.bonus

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	rm -f $(NAME) $(BONUS_MARK)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

bonus: $(BONUS_MARK)

$(BONUS_MARK): $(LIBFT) $(BONUS_OBJS)
	rm -f $(NAME)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(BONUS_OBJS)
	touch $(BONUS_MARK)

$(OBJ_DIR)/%_bonus.o: %_bonus.c ft_printf_bonus.h $(HEADERS) Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c $(HEADERS) Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
