/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_view.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:40:07 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/31 22:08:35 by zouazrou         ###   ########.fr       */
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

void    draw_textured_wall(t_game *g, int idx, int begin_x, int begin_y, int end_y, int wall_height);

void draw_wall_3d(t_game *g, int idx)
{
    double begin_x;
    double begin_y;
    double wall_height;
    int    end_y;
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
    // printf("begin_x [%.2f]\n", begin_x);
    // printf("begin_y [%.2f]\n\n", begin_y);
    draw_ceiling(g, begin_x, begin_y);
    // draw_wall(g, idx, begin_x, begin_y, wall_height);
    end_y = begin_y + wall_height;
    if (end_y > HEIGHT)
        end_y = HEIGHT;
    draw_textured_wall(g, idx, begin_x, begin_y, end_y, wall_height);
    draw_floor(g, begin_x, end_y);
}

// !=========================
void    draw_wall(t_game *g, int idx, int begin_x, int begin_y, int wall_height)
{
    int x;
    int end_y;
    int color;
    
    end_y = begin_y + wall_height;
    while (begin_y <= end_y)
    {
        x = 0;
        while (x < g->resolution)
        {
            color = create_rgb(g->ray[idx].color,g->ray[idx].color,g->ray[idx].color);
            put_pixel_in_image(g->img_3d, begin_x + x, begin_y, color);
            x++;
        }
        begin_y++;
    }
}


/*
! H
   * intersection position (x, y)
   * position = decimal_part(X / tilesz)
   * 0 <= position <= 1
   * Tex_X = Position * TEX_WIDTH
   * 0 <= Tex_X <= TEX_WIDTH
   * LOOP TEX_Y , WHEN DRAWING THE WALL
! v
   * intersection position (x, y)
   * position = decimal_part(y / tilesz)
   * 0 <= position <= 1
   * Tex_X = Position * TEX_WIDTH
   * 0 <= Tex_X <= TEX_WIDTH
   * LOOP TEX_Y , WHEN DRAWING THE WALL
*/