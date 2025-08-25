/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:51 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/25 12:35:57 by zouazrou         ###   ########.fr       */
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
# include "minilibx-linux/mlx.h"

// if your game window is 640×480, the projection plane is also 640×480.
// #define WIDTH 600
#define WIDTH 512
#define HEIGHT 512
#define tile_size 64

// #define WIDTH 3000
// #define HEIGHT 3000
// #define PI 22/7
#define PI 3.14159265358979323846

#define GREEN 0x00D100
#define BLCK_SHDW 0Xbfafb2
#define BLUE 0x3C6CAB
#define BROWN 0x61212D
#define BLACK 0x0
#define WHITE 0xffffff
#define YLW 0XFFFF00
#define RED 0XFF0000
/*

*/

typedef struct s_vd
{
    double     x;
    double     y;
} t_vd;

typedef struct s_vi
{
    int     x;
    int     y;
} t_vi;

typedef struct s_player
{
    t_vi    position;          // pixel
    // t_vd    direction;
    t_vd    plane;
    double  angle;
    
    // ? mv & rot speed
    int     move_speed; // pixel
    double  rotation_speed;
}           t_player;

typedef struct s_ray
{
    int     color;
    double  angle;    //
    t_vd    position; //
    double  distance; //
    bool    hit_wall; //
    t_vd    inc;      //


}   t_ray;

typedef struct s_game
{
    void    *mlx;
    void    *win_2d;
    void    *win_3d;
    void    *img_2d;
    void    *img_3d;
    
    /*MAP*/
    int     mapx;
    int     mapy;
    int     tilesz;
    
    /*position Player*/
    t_player    ply;

    /*Ray*/
    
    /*tilesize*/
    double  fov;
    int     resolution; // pixel
    // ray
    int     num_rays;
    t_ray   *ray;
    // PLANE
    double  distance_to_plane;
    /*FPS*/
    // double  time;
    // double  oldtime;
    // x-coordinate h
}   t_game;

int	create_rgb(int r, int g, int b);


t_ray    horizontal_hit(t_game *g, double ray_angle);
t_ray    vertical_hit(t_game *g, double ray_angle);

bool     check_map_bound(t_game *g, t_vd position);
int     close_win(void *ptr);
void    display(t_game *data);

int     distance(t_vd p0, t_vi p1);

int		keyboard(int keysym, t_game *map);
void    init_data(t_game *data);
int     close_win(void *ptr);
bool    is_wall(t_game *g, t_vd position);
double  normalize_angle(double radian);
// void draw_wall_3d(t_game *g, int ray, double ray_angle, int distance_p_to_w);
void draw_wall_3d(t_game *g, int idx);
// 
// void draw_wall_3d(t_game *g, int x0, int wall_height_on_screen, int col);

bool    FACING_UP(double angle);
bool    FACING_DOWN(double angle);
bool    FACING_RIGHT(double angle);
bool    FACING_LEFT(double angle);
void    ray_casting(t_game *g);

// utils function
void	*ft_calloc(size_t nmemb, size_t size);
void    draw_big_point(void *img, int x, int y,  int r, int col);
void    draw_ray(void *img, t_vi p0, t_vd p1, int color);
void    put_pixel_in_image(void *image, int x, int y, int col);
double  deg2rad(int degree);
void    ft_clean(t_game *g, bool ter);






// --------------------------
// Reset
# define RESET   "\033[0m"

// Regular Colors
# define TXT_BLACK   "\033[30m"
# define TXT_RED     "\033[31m"
# define TXT_GREEN   "\033[32m"
# define TXT_YELLOW  "\033[33m"
# define TXT_BLUE    "\033[34m"
# define TXT_MAGENTA "\033[35m"
# define TXT_CYAN    "\033[36m"
# define TXT_WHITE   "\033[37m"

// Bold
# define BOLD    "\033[1m"
#endif