/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:51 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/23 21:37:20 by zouazrou         ###   ########.fr       */
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

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *image;
    
    /*MAP*/
    int     mapx;
    int     mapy;
    int     tilesz;
    
    /*position Player*/
    t_vi    p;          // pixel
    double  pa;
    t_vd    d;
    t_vd    plane;
    int     move_speed; // pixel
    double  rotation_speed;
    
    /*tilesize*/
    double  fov;
    int     resolution; // pixel
    int     num_rays;
    /*FPS*/
    double  time;
    double  oldtime;
    // x-coordinate h
}   t_game;


t_vd    horizontal_hit(t_game *g, double ray_angle);
t_vd    vertical_hit(t_game *g, double ray_angle);

bool     check_map_bound(t_game *g, t_vd position);
void    draw_big_point(void *img, int x, int y,  int r, int col);
int     close_win(void *ptr);
void    draw_ray(void *img, t_vi p0, t_vd p1, int color);
// void    draw_line(void *img, t_vd p0, t_vd p1, int color);
void    draw_dir(void *img, t_vi point, t_vd dir, int len, int color);
void    display(t_game *data);

int     distance(t_vd p0, t_vi p1);

int		keyboard(int keysym, t_game *map);
void    init_data(t_game *data);
void    put_pixel_in_image(void *image, int x, int y, int col);
int     close_win(void *ptr);
double  deg_to_rad(int degree);
bool    is_wall(t_game *g, t_vd position);
double  normalize_angle(double radian);

bool    FACING_UP(double angle);
bool    FACING_DOWN(double angle);
bool    FACING_RIGHT(double angle);
bool    FACING_LEFT(double angle);
void    ray_casting(t_game *g);

#endif