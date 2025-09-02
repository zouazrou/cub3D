/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:41:55 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/02 23:06:30 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef structures_h
# define STRUCTURES_H

typedef long long t_ms;

typedef enum e_dir
{
    NORTH = 1, // UP
    SOUTH,     // DOWN
    EAST,      // RIGHT
    WEST,      // LEFT
} t_dir;

typedef enum e_axis
{
    VERTICAL = 10,
    HORIZONTAL,
} t_axis;

typedef struct s_vd
{
    double x;
    double y;
} t_vd;

typedef struct s_player // ! dir baalk
{
    t_vd    position;
    double  angle;

    // ? mv & rot speed
    double  move_speed;
    double  rotation_speed;
} t_player;

typedef struct s_ray
{
    int     color;
    double  angle;
    t_vd    inter;
    double  distance;
    bool    hit_wall;
    t_vd    inc;
    t_dir   side;
    t_axis  axis;
} t_ray;

typedef struct s_img
{
    void    *img;
    char    *pixels;
    int     bpp;
    int     line;
    int     endian;
}   t_img;

typedef struct s_texture
{
    int     w;
    int     h;
    t_img   image;
    char    *filename;
} t_texture;

typedef struct s_game
{
    void        *mlx;
    void        *win_3d;
    t_img       img_3d;
    
    t_texture   north;
    t_texture   south;
    t_texture   west;
    t_texture   east;

    int floor_color;
    int ceiling_color;

    /*MAP*/
    int mapx;
    int width;
    int height;
    int mapy;
    int tilesz;

    t_player ply;


    double fov;
    int resolution;
    int num_rays;
    t_ray *ray;
    double distance_to_plane;
} t_game;

#endif