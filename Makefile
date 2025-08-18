NAME = cub3D
CC = cc
# CFLAGS = -Wall -Wextra -Werror -lm
CFLAGS = -g 
MLX_FLAGS = -lXext -lX11

SRC = main.c init.c utils.c keypress.c

MLX_PATH = minilibx-linux/

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) 
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJ) minilibx-linux/libmlx.a  -o $(NAME)
	@echo "exec:✅"

$(OBJ) : $(SRC) cub3d.h
	@$(CC) -c $(CFLAGS) $(SRC)
	@echo "OBJ:✅"

clean :
	@rm -f $(OBJ)
	@echo "clean:✅"

fclean :
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "fclean:✅"

.PHONY : clean fclean