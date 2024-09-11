# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 14:09:36 by pesilva-          #+#    #+#              #
#    Updated: 2024/09/11 17:04:36 by pesilva-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC_DIR = ./src
OBJ_DIR = ./obj
MINILIBX_DIR = ./minilibx-linux
CC = cc
CFLAGS = -Wall -Werror -Wextra -O3 -g

SRC_FILES = main.c \
			init.c \
			ft_error.c \
			math_utils.c \
			render.c \
			string_utils.c \
			window.c \
			events.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

$(NAME): $(OBJ_DIR) $(OBJS)
	$(MAKE) -C $(MINILIBX_DIR)
	$(CC) $(CFLAGS) $(OBJS) -I./mlx_linux/ -o $(NAME) -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	clean -C $(MINILIBX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
