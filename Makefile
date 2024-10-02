# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 14:09:36 by pesilva-          #+#    #+#              #
#    Updated: 2024/09/26 20:07:58 by pesilva-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC_DIR = ./src
OBJ_DIR = ./obj
MINILIBX_DIR = ./minilibx-linux
CC = cc
CFLAGS = -Wall -Werror -Wextra -Ofast -g -I/minilibx-linux -Imlx_linux

SRC_FILES = main.c \
			init.c \
			ft_error.c \
			math_utils.c \
			render.c \
			string_utils.c \
			window.c \
			events.c \
			color.c \
			math_utils2.c \
			utils.c \

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
	$(MAKE) clean -C $(MINILIBX_DIR)

fclean: clean
	#$(MAKE) fclean -C $(MINILIBX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
