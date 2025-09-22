NAME = cub3d
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
HEADER_FILE = cub3d.h  structures.h

# libs
MLX_FLAGS = -lXext -lX11
MLX_PATH = minilibx-linux/
MLX_LIB = $(MLX_PATH)libmlx.a
LIBFT = libft/libft.a
LIBS = $(LIBFT) $(MLX_LIB) $(MLX_FLAGS)

SRC = $(addprefix src/, main.c init.c utils.c utils2.c keypress.c raycasting.c \
	horizontal.c display.c clean.c check_direction.c \
	3d_view.c draw_texture.c raycasting_utils.c\
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	color.c data_utils.c file_utils.c \
	map_utlis.c map_validate.c parser.c  \
	read_map.c textures.c utils3.c)

OBJ = $(SRC:.c=.o)

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

.PHONY : all re clean fclean
