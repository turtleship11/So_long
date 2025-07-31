# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 11:30:19 by jaeklee           #+#    #+#              #
#    Updated: 2025/07/31 15:04:53 by jaeklee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I../libft
SRCDIR = src

NAME = libftprintf.a

SRCS=  ft_printf_hex.c ft_printf_ptr.c ft_printf_un.c \
		ft_printf_utils.c ft_printf.c ft_printf_nbr.c\

OBJS = $(SRCS:.c=.o)

.SECONDARY: $(OBJS)

all: $(NAME)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@ 
	
$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


test:	main.c $(NAME)
		$(CC) -o $@ $(CFLAGS) main.c $(NAME)  
