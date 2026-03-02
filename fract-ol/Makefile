# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/12 02:16:58 by kyanagis          #+#    #+#              #
#    Updated: 2025/07/12 02:16:58 by kyanagis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME       = fractol

SRC_DIR    = src
OBJ_DIR    = obj
LIBFT_DIR  = libft
PRINTF_DIR = $(LIBFT_DIR)/ft_printf
MLX_DIR    = minilibx-linux

CC         = cc
OPTFLAGS   = -Ofast -march=native -ffast-math -fno-math-errno -funroll-loops -flto
CFLAGS     = -Wall -Wextra -Werror $(OPTFLAGS) \
             -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR)

SRC        = $(SRC_DIR)/burning_ship.c \
             $(SRC_DIR)/color.c \
             $(SRC_DIR)/hooks.c \
             $(SRC_DIR)/init.c \
             $(SRC_DIR)/julia.c \
             $(SRC_DIR)/main.c \
             $(SRC_DIR)/mandelbrot.c \
             $(SRC_DIR)/render.c \
             $(SRC_DIR)/sierpinski_gasket.c

OBJ        = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

LIBFT      = $(LIBFT_DIR)/libft.a
PRINTF     = $(PRINTF_DIR)/libftprintf.a
MLX        = $(MLX_DIR)/libmlx.a

LDFLAGS    = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz \
             -L$(LIBFT_DIR) -lft \
             -L$(PRINTF_DIR) -lftprintf \
             -flto

PRINTF_MAKE = $(MAKE) -C $(PRINTF_DIR) LIBFT_DIR=..

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(PRINTF) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(PRINTF): $(LIBFT)
	$(PRINTF_MAKE)

$(MLX_DIR):
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

$(MLX): | $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(PRINTF_MAKE) clean
	-$(MAKE) -C $(MLX_DIR) clean 2>/dev/null || true
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(PRINTF_MAKE) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
