CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft/include -IMLX42/include -IFt_printf

NAME = so_long

SRCS = main.c 1_map.c 1_map2.c 3_textures.c 4_key.c helper.c 2_valid.c \
		helper2.c

OBJS = $(SRCS:.c=.o)

MLX_DIR = MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS = -I$(MLX_DIR)/include
MLX_LINK_FLAGS = $(MLX_LIB) -ldl -lglfw -pthread -lm

LIBFT_LIB = libft/libft.a
PRINTF_LIB = Ft_printf/libftprintf.a

.SECONDARY: $(OBJS)

all: $(MLX_LIB) $(LIBFT_LIB) $(PRINTF_LIB) $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	$(MAKE) -C libft

$(PRINTF_LIB):
	$(MAKE) -C Ft_printf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_LIB) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LINK_FLAGS) $(LIBFT_LIB) $(PRINTF_LIB) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean
	$(MAKE) -C Ft_printf clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	$(MAKE) -C Ft_printf fclean

re: fclean all


# CC = cc
# CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft/include -IMLX42/include


# NAME = so_long

# SRCS = main.c 1_map.c 1_map2.c 3_textures.c 4_key.c helper.c 2_valid.c \
# 		helper2.c


# OBJS = $(SRCS:.c=.o)

# .SECONDARY: $(OBJS)
# MLX_DIR = MLX42
# MLX_LIB = $(MLX_DIR)/build/libmlx42.a
# MLX_FLAGS = -I$(MLX_DIR)/include
# MLX_LINK_FLAGS = $(MLX_LIB) -ldl -lglfw -pthread -lm
# LIBFT_LIB = libft/libft.a
# GNL_LIB = gnl/gnl.a 

# all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

# $(MLX_LIB):
# 	$(MAKE) -C $(MLX_DIR)

# $(LIBFT_LIB):
# 	$(MAKE) -C libft

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_LIB)
# 	$(CC) $(CFLAGS) $(OBJS) $(MLX_LINK_FLAGS) $(LIBFT_LIB) -o $(NAME)

# clean:
# 	rm -f $(OBJS)
# 	$(MAKE) -C libft clean

# fclean: clean
# 	rm -f $(NAME)
# 	$(MAKE) -C libft fclean

# re: fclean all
