SRC = main.c draw_grid.c caster.c map_mock.c draw_map.c draw_scene.c
OBJ = $(SRC:.c=.o)
CC = gcc
RM = rm -f
CFLAGS = -I$(MLX42)/include #-Wall -Wextra -Werror -g

NAME = walls

MLX42 = ../../MLX42
libmlx42 = $(MLX42)/libmlx42.a

LINK_OPTIONS = -ldl -lglfw -pthread -lm

all: $(NAME)

$(libmlx42):
		make -C $(MLX42)

$(NAME):	$(OBJ) $(libmlx42)
		$(CC) $(OBJ) $(libmlx42) $(CFLAGS) -o $(NAME) $(LINK_OPTIONS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re