NAME = cub3D
CC = cc
# CFLAGS = -Wall -Wextra -Werror  -g
CFLAGS = -g 
HEADER_FILE = cub3d.h  structures.h
MLX_FLAGS = -lXext -lX11

SRC = main.c init.c utils.c utils2.c keypress.c raycasting.c\
	horizontal.c display.c clean.c check_direction.c\
	3d_view.c draw_texture.c

MLX_PATH = minilibx-linux/

OBJ = $(SRC:.c=.o)

LIBS = minilibx-linux/libmlx.a $(MLX_FLAGS) -lm
all : $(NAME)

$(NAME) : $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "\\033[1m\\033[36mexec:⚙️\\033[0m"

$(OBJ) : $(SRC) $(HEADER_FILE) Makefile
	$(CC) -c $(CFLAGS) $(SRC)
	@echo "\\033[1m\\033[32mOBJ:📁\\033[0m"

re : fclean all

clean :
	@rm -f $(OBJ)
	@echo "\\033[1m\\033[35mclean:🧹"

fclean :
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "\\033[1m\\033[31mfclean:🗑️\\033[0m"

.PHONY : clean fclean