SRC = hello.c
OBJ = $(SRC:.c=.o)
CC = gcc
RM = rm -f
CFLAGS = -I$(MLX42)/include #-Wall -Wextra -Werror

NAME = hello

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
		make -C $(MLX42) clean

fclean:		clean
		$(RM) $(NAME)
		make -C $(MLX42) fclean

re:			fclean all

.PHONY:		all clean fclean re