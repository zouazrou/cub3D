/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_view.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:40:07 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/30 16:56:13 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int bpp;
extern int line_bytes;
extern int endian;
extern int map[8][8];

void    draw_ceiling(t_game *g, int begin_x, int begin_y)
{
    int x;
    int y;

    for (y = 0; y < begin_y; y++)
    {
        for (x = 0; x < g->resolution; x++)
        {
            // if (!is_outside_window(begin_x + x, y))
                put_pixel_in_image(g->img_3d, begin_x+x, y, g->ceiling_color);
        }
    }
}

void    draw_floor(t_game *g, int begin_x, int begin_y)
{
    int x;
    int y;

    for (y = begin_y; y < HEIGHT; y++)
    {
        for (x = 0; x < g->resolution; x++)
        {
            // if (!is_outside_window(begin_x + x, y))
                put_pixel_in_image(g->img_3d, begin_x+x, y, g->floor_color);
        }
    }
}

/*
    ! texture
    * indicate any cell in map ray hit (x, y) 
*/
void    draw_wall(t_game *g, int idx, int begin_x, int begin_y, int wall_height);

void    draw_textured_wall(t_game *g, int idx, int begin_x, int begin_y, int wall_height);

void draw_wall_3d(t_game *g, int idx)
{
    double begin_x;
    double begin_y;
    double wall_height;
    t_ray *r;

    r = g->ray + idx;
    
    // ? fix fish eye 
    r->distance = fix_fish_eye(g, idx);
    /****LIGHT*****/
    // r->color *= (LIGHT_LVL / r->distance);
    // if (r->color < 0)
    //     r->color = 0;
    // if (r->color > 255)
    //     r->color = 255;
    /*********/
    wall_height = (g->tilesz * g->distance_to_plane) / r->distance;
    begin_x = idx * g->resolution;
    begin_y = (HEIGHT/2.0) - (wall_height/2.0);
    if (begin_y < 0)
        begin_y = 0;
    if (wall_height >= HEIGHT)
        wall_height = HEIGHT-1;
    // texturing calculations
    
    printf("begin_x [%.2f]\n", begin_x);
    printf("begin_y [%.2f]\n\n", begin_y);
    //
    draw_ceiling(g, begin_x, begin_y);
    draw_wall(g, idx, begin_x, begin_y, wall_height);
    draw_floor(g, begin_x, begin_y + wall_height);
}

// !=========================
void    draw_wall(t_game *g, int idx, int begin_x, int begin_y, int wall_height)
{
    int x;
    int y;
    
    for (y = 0; y < wall_height; y++)
    {
        for (x = 0; x < g->resolution; x++)
        {
            // if (!is_outside_window(begin_x + x, begin_y + y))
                put_pixel_in_image(g->img_3d, begin_x + x, begin_y + y, create_rgb(g->ray[idx].color,g->ray[idx].color,g->ray[idx].color));
        }
    }
}
/*

int    get_pixel_color(t_game *g, int x, int y)
{
    int offset;
    int tex_x;
    int tex_y;
    
    if (x < 0 || y < 0)
        return (0);
    if (x >= 64 ||y >= 64)
        return (0); 
    offset = (y * g->west->line) + (x * (g->west->bpp / 8));
    return (*(unsigned int *)(g->west->pixels + offset));
}

void    draw_textured_wall(t_game *g, int idx, int begin_x, int begin_y, int wall_height)
{
    int x;
    int y;
    int tex_x;
    int tex_y;
    
    for (y = 0; y < wall_height; y++)
    {
        for (x = 0; x < g->resolution; x++)
        {
            tex_x = (int)((x / wall_height) * 64);
            tex_y = (int)((y / wall_height) * 64);
            put_pixel_in_image(g->img_3d, begin_x + x, begin_y + y, get_pixel_color(g, tex_x , y));   
        }
    }
    
}
*/