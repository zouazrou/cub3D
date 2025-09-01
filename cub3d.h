/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:51 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/31 22:57:58 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/time.h>
# include "minilibx-linux/mlx.h"
# include "structures.h"

# define WIDTH 800
# define HEIGHT 600
# define FPS 30

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


/*

*/


int create_rgb(int r, int g, int b);

t_ray horizontal_hit(t_game *g, double ray_angle);
t_ray vertical_hit(t_game *g, double ray_angle);

void display(t_game *data);

double distance(t_vd p0, t_vd p1);

bool    is_outside_window(int x, int y);
int keyboard(int keysym, t_game *map);
void init_data(t_game *data);
// int close_win(void *ptr);
bool is_wall(t_game *g, t_vd position);
double normalize_angle(double radian);
void draw_3d_view(t_game *g, int idx);
//

bool FACING_UP(double angle);
bool FACING_DOWN(double angle);
bool FACING_RIGHT(double angle);
bool FACING_LEFT(double angle);
void ray_casting(t_game *g);
double  fix_fish_eye(t_game *g, int index);

// utils function
void    *ft_calloc(size_t nmemb, size_t size);
void    draw_big_point(void *img, int x, int y, int r, int col);
void    draw_ray(void *img, t_vd p0, t_vd p1, int color);
void    put_pixel_in_image(void *image, int x, int y, int col);
void    fill_img(void *img, int col, int h, int w);
int     ft_clean(int keysym, t_game *g);
double  deg2rad(int degree);
void    change_angle(int keysym, t_game *g);
char	*ft_strdup(const char *s);
// int    get_pixel_color(t_game *g, int x, int y);

// --------------------------
// Reset
#define RESET "\033[0m"

// Regular Colors
#define TXT_BLACK "\033[30m"
#define TXT_RED "\033[31m"
#define TXT_GREEN "\033[32m"
#define TXT_YELLOW "\033[33m"
#define TXT_BLUE "\033[34m"
#define TXT_MAGENTA "\033[35m"
#define TXT_CYAN "\033[36m"
#define TXT_WHITE "\033[37m"

// Bold
#define TXT_BOLD "\033[1m"
#endif