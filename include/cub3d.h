/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:51 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/22 14:32:55 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/time.h>
# include "../minilibx-linux/mlx.h"
# include "structures.h"
# include "../src/get_next_line/get_next_line.h"
# include "../libft/libft.h"

# define WIDTH 800
# define HEIGHT 600
# define FPS 60

# define PI 3.14159265358979323846
# define LIGHT_LVL 40
# define MINIMAP_SIZE 0.2
# define GREEN 0x00D100
# define BLCK_SHDW 0Xbfafb2
# define BLUE 0x3C6CAB
# define BROWN 0x61212D
# define BLACK 0x0
# define WHITE 0xffffff
# define YLW 0XFFFF00
# define RED 0XFF0000
# define LIGHT_BLUE 0x87CEEB
# define DARK_GRAY 0x444444
# define CYAN 0x00FFFF




t_ray horizontal_hit(double ray_angle);
t_ray vertical_hit(double ray_angle);

void display(t_game *data);

double distance(t_vd p0, t_vd p1);
int	destroy_notify_func(t_game *game);
int keyboard(int keysym, t_game *map);
void init_game(t_game *data);
// int close_win(void *ptr);
bool is_wall(t_ray *ray);
double normalize_angle(double radian);
void draw_3d_view(int idx);
int     frames(t_game *data);
//
void    draw_cube(int idx, int begin_y, int end_y, int wall_height);
// void    draw_colorful_cube(int idx, int begin_x, int begin_y, int wall_height);
void	init_dirs(int dy[4], int dx[4]);

bool facing_up(double angle);
bool facing_down(double angle);
bool facing_right(double angle);
bool facing_left(double angle);
void ray_casting(t_game *g);
double  fix_fish_eye(int index);

// utils function
int	row_len(const char *row);
void	choose_nearest(t_ray *ray, t_ray *ray_h, t_ray *ray_v);
void	increment_to_the_wall(t_ray *ray);
t_ms	get_time(void);
bool	check_win_bound(t_ray *ray);
void    *ft_calloc(size_t nmemb, size_t size);
void    put_pixel_in_image(int x, int y, int col);
int     ft_clean(int keysym, t_game *g);
double  deg2rad(int degree);
void    change_angle(int keysym, t_game *g);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);

// ! Parsing Part
int		validate_rgb_part(char *part, int *value);
void	init_ray_struct(t_ray *ray, double ray_angle);
t_data	*init_data(char *input, int *fd);
int		parse_identifiers_and_map(int fd, t_data *data);
int		is_color_line(char *s);
void 	parse_color(char *color, t_data *data);
void    ft_perror(char *str);
void 	free_data(t_data *data);
void 	data_init(t_data *data);
int		validate_map(t_data *data);
int		after_last_line(t_data *data);
char	**my_realloc(char **old, int old_size);
int		read_map(int fd, t_data *data);
int		is_valid_char(char c);
int		check_neighbors(char **map, int y, int x);
int		check_all_exist(t_data *data);
void	if_process(t_data *data, char *tmp, int *flag);
void	free_str_array(char **str);
char	*skip_ws(char *s);
int		is_all_digits(const char *str);
t_data	*parse_input(char *input);
// --------------------------
t_game *get_addr_t_game(t_game *ptr);
t_data *get_addr_t_data(t_data *ptr);

// Regular Colors
#define RESET "\033[0m"
#define TXT_BLACK "\033[30m"
#define TXT_RED "\033[31m"
#define TXT_GREEN "\033[32m"
#define TXT_YELLOW "\033[33m"
#define TXT_BLUE "\033[34m"
#define TXT_MAGENTA "\033[35m"
#define TXT_CYAN "\033[36m"
#define TXT_WHITE "\033[37m"

#endif