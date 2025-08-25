NAME = cub3D
CC = cc
# CFLAGS = -Wall -Wextra -Werror -lm
CFLAGS = -g 
MLX_FLAGS = -lXext -lX11

SRC = main.c init.c utils.c utils2.c keypress.c ray.c horizontal.c display.c clean.c

MLX_PATH = minilibx-linux/

OBJ = $(SRC:.c=.o)

LIBS = minilibx-linux/libmlx.a $(MLX_FLAGS) -lm
all : $(NAME)

$(NAME) : $(OBJ) 
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "exec:✅"

$(OBJ) : $(SRC) cub3d.h
	@$(CC) -c $(CFLAGS) $(SRC)
	@echo "OBJ:✅"

re : fclean all

clean :
	@rm -f $(OBJ)
	@echo "clean:✅"

fclean :
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "fclean:✅"

.PHONY : clean fclean