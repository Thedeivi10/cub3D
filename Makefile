# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jotrujil <jotrujil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/15 21:33:55 by davigome          #+#    #+#              #
#    Updated: 2025/06/07 13:38:16 by jotrujil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g
MLX42		= ./MLX42
LIBFT		= ./libft
INCLUDES	= -I$(MLX42)/include -I$(LIBFT)/include -I ./include
LIBS		= -L$(MLX42)/build -lmlx42 -lglfw -ldl -lm -lpthread -L$(LIBFT) -lft

#TESTS

VALGRIND = valgrind --suppressions=suppressions.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3D maps/p.cub


# Colores
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
RESET = \033[0m

SRC_DIR			= ./sources

OBJ_DIR			= ./obj

SRC_FILES		= cub3D.c\
					utils.c\
					utils_2.c\
					elemts.c\
					check_nswe.c\
					check_aux_fc.c\
					check_fc.c\
					checks.c\
					checks_2.c\
					checks_3.c\
					run.c\
					input.c\
					input2.c\
					render.c\

OBJS				= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT)/libft.a $(MLX42)/build/libmlx42.a $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
	@echo "$(GREEN)Executable for cub3D launched successfully!$(RESET)"

$(LIBFT)/libft.a:
	@$(MAKE) -C $(LIBFT)

$(MLX42)/build/libmlx42.a:
	@echo "$(YELLOW)Building MLX42 library...$(RESET)"
	@cmake -S $(MLX42) -B $(MLX42)/build
	@cmake --build $(MLX42)/build -j4
	@echo "$(GREEN)MLX42 library built successfully!$(RESET)"

all:$(NAME)

valgrind:
	$(VALGRIND)

clean:
	@$(MAKE) -C $(LIBFT) clean
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r $(MLX42)/build

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
