/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:51 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/25 09:55:23 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../mondatory/src/get_next_line/get_next_line.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include "structures.h"

# define WIDTH 800
# define HEIGHT 600
# define FPS 60

# define PI 3.14159265358979323846

t_ray	horizontal_hit(double ray_angle);
t_ray	vertical_hit(double ray_angle);

void	display(t_game *data);

double	distance(t_vd p0, t_vd p1);
int		destroy_notify_func(t_game *game);
int		keyboard(int keysym, t_game *map);
void	init_game(t_game *data);
bool	is_wall(t_ray *ray);
double	normalize_angle(double radian);
void	draw_3d_view(int idx);
int		frames(t_game *data);
void	draw_cube(int idx, int begin_y, int end_y, int wall_height);
void	init_dirs(int dy[4], int dx[4]);

bool	facing_up(double angle);
bool	facing_down(double angle);
bool	facing_right(double angle);
bool	facing_left(double angle);
void	ray_casting(t_game *g);
double	fix_fish_eye(int index);

// ! utils function
int		row_len(const char *row);
void	choose_nearest(t_ray *ray, t_ray *ray_h, t_ray *ray_v);
void	increment_to_the_wall(t_ray *ray);
t_ms	get_time(void);
bool	check_win_bound(t_ray *ray);
void	*ft_calloc(size_t nmemb, size_t size);
void	put_pixel_in_image(int x, int y, int col);
int		ft_clean(int keysym, t_game *g);
double	deg2rad(int degree);
void	change_angle(int keysym, t_game *g);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);
void	convert_xpm_to_images(t_game *g);

// ! Parsing Part
int		validate_rgb_part(char *part, int *value);
void	init_ray_struct(t_ray *ray, double ray_angle);
t_data	*init_data(char *input, int *fd);
int		parse_identifiers_and_map(int fd, t_data *data);
int		is_color_line(char *s);
void	parse_color(char *color, t_data *data);
void	ft_perror(char *str);
void	free_data(t_data *data);
void	data_init(t_data *data);
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

t_game	*get_addr_t_game(t_game *ptr);
t_data	*get_addr_t_data(t_data *ptr);

#endif