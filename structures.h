/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:41:55 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/30 16:23:01 by zouazrou         ###   ########.fr       */
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
    t_vd    position; // pxl
    double  angle;  // rad

    // ? mv & rot speed
    double  move_speed; // pxl
    double  rotation_speed;
} t_player;

typedef struct s_ray
{
    int     color;
    double  angle;    // rad
    t_vd    position;   // pxl
    double  distance; //
    bool    hit_wall;   //
    t_vd    inc;        // pxl
    t_dir   side;
    t_axis  axis; // v or h
} t_ray;

typedef struct s_texture
{
    int     w;
    int     h;
    char    *file_name;
    void    *img;
    char    *pixels;

    /*******/
    int bpp;
    int line;
    int endian;
}   t_texture;

typedef struct s_game
{
    void        *mlx;
    void        *win_3d;
    void        *img_3d;
    
    t_texture   *north;
    t_texture   *south;
    t_texture   *west;
    t_texture   *east;

    int floor_color;
    int ceiling_color;

    /*MAP*/
    int mapx;
    int mapy;
    int tilesz;

    /*position Player*/
    t_player ply;

    /*Ray*/

    /*tilesize*/
    double fov;
    int resolution; // pixel
    // ray
    int num_rays;
    t_ray *ray;
    // PLANE
    double distance_to_plane;
} t_game;

#endif