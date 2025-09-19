NAME = cub3D
CC = cc -g
CFLAGS = -Wall -Wextra -Werror  -g
HEADER_FILE = cub3d.h  structures.h
MLX_FLAGS = -lXext -lX11

SRC = main.c init.c utils.c utils2.c keypress.c raycasting.c\
	horizontal.c display.c clean.c check_direction.c\
	3d_view.c draw_texture.c parssing.c\
	get_next_line.c get_next_line_utils.c

MLX_PATH = minilibx-linux/

MLX_LIB = $(MLX_PATH)libmlx.a

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

LIBS = $(LIBFT) $(MLX_LIB) $(MLX_FLAGS)

all : $(NAME)


$(LIBFT) :
	@make -C libft/
$(MLX_LIB) :
	@make -C $(MLX_PATH)

$(NAME) : $(OBJ) $(LIBS) 
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -lm -o $(NAME)
	@echo "\\033[1m\\033[36mexec:⚙️\\033[0m"

%.o : %.c $(HEADER_FILE) 
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "\\033[1m\\033[32mOBJ:📁\\033[0m"

re : fclean all

clean :
	@rm -f $(OBJ)
	@make clean -C libft/
	@echo "\\033[1m\\033[35mclean:🧹"

fclean :
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@make fclean -C libft/
	@echo "\\033[1m\\033[31mfclean:🗑️\\033[0m"

.PHONY : clean fclean
