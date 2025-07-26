CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft/include -IMLX42/include


NAME = so_long

SRCS = main.c 

.SECONDARY: $(OBJS)

OBJS = $(SRCS:.c=.o)


MLX_DIR = MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS = -I$(MLX_DIR)/include
MLX_LINK_FLAGS = $(MLX_LIB) -ldl -lglfw -pthread -lm
LIBFT_LIB = libft/libft.a
GNL_LIB = gnl/gnl.a 

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	$(MAKE) -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LINK_FLAGS) $(LIBFT_LIB) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(MLX_DIR) fclean
	$(MAKE) -C libft fclean

re: fclean all
