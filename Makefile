# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 14:09:36 by pesilva-          #+#    #+#              #
#    Updated: 2024/05/24 14:31:42 by pesilva-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol.a

OBJS = OBJ
SRC = SRC
MINILIBX_DIR = ./mlx_linux
MAIN_SRC = main.c
SRC_FILES = main.c
			string_utils.C
			ft_error.c

CC= cc
CFLAGS = -Wall -Werror -Wextra -fast

all : $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
		$(MAKE) -C $(MINILIBX_DIR)
		@ar -crs $(NAME) $(OBJ)

		@$(CC) $(CFLAGS) -I./mlx_linux/ -o $(PROGRAM) $(MAIN_SRC) $(NAME) -lmlx -lXext -lX11 -lm -lz

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) clean -C $(MINILIBX_DIR)
	@rm -f $(NAME) $(PROGRAM)

re: fclean all

.PHONY: all clean fclean re program val show