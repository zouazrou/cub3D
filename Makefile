NAME = cub3D

NAME_BONUS = cub3d_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

# libs
MLX_FLAGS = -lXext -lX11
MLX_PATH = minilibx-linux/
MLX_LIB = $(MLX_PATH)libmlx.a
LIBFT = libft/libft.a
LIBS = $(LIBFT) $(MLX_LIB) $(MLX_FLAGS)

SRC = $(addprefix mondatory/src/, main.c init.c utils.c utils2.c keypress.c raycasting.c \
	display.c clean.c check_direction.c \
	3d_view.c draw_texture.c raycasting_utils.c\
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	color.c data_utils.c file_utils.c \
	map_utlis.c map_validate.c parser.c  \
	read_map.c textures.c utils3.c)

SRC_BNS = $(addprefix bonus/src/, main_bonus.c init_bonus.c utils_bonus.c utils2_bonus.c keypress_bonus.c raycasting_bonus.c \
	display_bonus.c clean_bonus.c check_direction_bonus.c \
	3d_view_bonus.c draw_texture_bonus.c raycasting_utils_bonus.c\
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	color_bonus.c data_utils_bonus.c file_utils_bonus.c \
	map_utlis_bonus.c map_validate_bonus.c parser_bonus.c  \
	read_map_bonus.c textures_bonus.c utils3_bonus.c)

OBJ = $(SRC:.c=.o)

OBJ_BNS = $(SRC_BNS:.c=.o)

all : $(NAME)

$(LIBFT) :
	@make -C libft/

$(MLX_LIB) :
	@make -C $(MLX_PATH)

$(NAME) : $(OBJ) $(LIBS) 
	@echo "\\033[1m\\033[32mOBJ:📁\\033[0m"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -lm -o $(NAME)
	@echo "\\033[1m\\033[36mexec:⚙️\\033[0m"

bonus : $(NAME_BONUS)

$(NAME_BONUS) : $(OBJ_BNS) $(LIBFT)
	@echo "\\033[1m\\033[32mOBJ_BNS:📁\\033[0m"
	@$(CC) $(CFLAGS) $(OBJ_BNS) $(LIBS) -lm -o $(NAME_BONUS)
	@echo "\\033[1m\\033[36mexec bonus:⚙️\\033[0m"

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

re : fclean all

clean :
	@rm -f $(OBJ)
	@rm -f $(OBJ_BNS)
	@make clean -C libft/
	@echo "\\033[1m\\033[35mclean:🧹"

fclean :
	@rm -f $(OBJ)
	@rm -f $(OBJ_BNS)
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@make fclean -C libft/
	@echo "\\033[1m\\033[31mfclean:🗑️\\033[0m"

.PHONY : all re clean fclean
