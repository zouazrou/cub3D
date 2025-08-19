/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:51 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/19 10:31:06 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>    
# include <math.h>    
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"


#define W 512
#define H 512

// #define W 3000
// #define H 3000
#define PI 3.1415926535

#define GREEN 0x00D100
#define BLCK_SHDW 0Xbfafb2
#define BLACK 0x0
#define WHITE 0xffffff
#define YLW 0XFFFF00
#define RED 0XFF0000
/*

*/

typedef struct t_vd
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
    
    /*position Player*/
    t_vi  p;
    /*direction Player*/
    t_vd  d;
    /*Angle Player*/
    double pa;
    /* !Fov Player*/
    t_vd  plane;
    /*speed ply*/
    int  sp;
    /*FPS*/
    double  time;
    double  oldtime;
    // x-coordinate h
}   t_game;

void    draw_big_point(void *img, t_vi crd, int r, int col);
int     close_win(void *ptr);
void    draw_ray(t_game *g);
void    display(t_game *data);

void    DDA(t_vi a, t_vi b, t_game *data, int col);

int		keyboard(int keysym, t_game *map);
void    init_data(t_game *data);
void    put_pixel_in_image(void *image, int x, int y, int col);
int     close_win(void *ptr);
#endif