SRC = main.c
OBJ = $(SRC:.c=.o)
CC = gcc
RM = rm -f
CFLAGS = -I$(MLX42)/include -I$(LIBFT) -g#-Wall -Wextra -Werror

NAME = designer

MLX42 = ../../lib/MLX42
libmlx42 = $(MLX42)/libmlx42.a

LIBFT = ../../lib/libft
libft = $(LIBFT)/libft.a

LINK = -lglfw -pthread -lm -framework Cocoa -framework OpenGL -framework \
		IOKit -L"/Users/$(USER)/.brew/opt/glfw/lib/"
all: $(NAME)

$(libmlx42):
		make -C $(MLX42)

$(libft):
		make -C $(LIBFT)

$(NAME):	$(OBJ) $(libmlx42) $(libft)
		$(CC) $(OBJ) $(libmlx42) $(libft) $(CFLAGS) -o $(NAME) $(LINK)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re