NAME = cub3D

# CFLAGS = -Wall -Wextra -Werror -lm
CFLAGS = -g -lm
MLX_FLAGS = -lXext -lX11

SRC = main.c init.c

MLX_PATH = minilibx-linux/

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(MLX_FLAGS) $(OBJ) minilibx-linux/libmlx.a  -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

.PHONY : clean fclean