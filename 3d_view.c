/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_view.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:40:07 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/02 21:58:38 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[16][16];

void    draw_ceiling(t_game *g, int begin_x, int begin_y)
{
    int x;
    int y;

    y = -1;
    while (++y < begin_y)
    {
        x = -1;
        while (++x < g->resolution)
        {
            if (!is_outside_window(begin_x + x, y))
                put_pixel_in_image(&g->img_3d, begin_x+x, y, g->ceiling_color);
        }
    }
}

void    draw_floor(t_game *g, int begin_x, int begin_y)
{
    int x;
    int y;

    y = begin_y-1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < g->resolution)
        {
            if (!is_outside_window(begin_x + x, y))
                put_pixel_in_image(&g->img_3d, begin_x+x, y, g->floor_color);
        }
    }
}

/*
    ! texture
    * indicate any cell in map ray hit (x, y) 
*/
void    draw_colorful_wall(t_game *g, int idx, int begin_x, int begin_y, int wall_height);

void    draw_textured_wall(t_game *g, int idx, int begin_x, int begin_y, int end_y, int wall_height);

void draw_3d_view(t_game *g, int idx)
{
    int begin_x;
    int begin_y;
    int end_y;
    int wall_height;
    t_ray *r;

    r = g->ray + idx;
    
    // ? fix fish eye 
    r->distance = fix_fish_eye(g, idx);
    wall_height = (g->tilesz * g->distance_to_plane) / r->distance;
    
    begin_y = (HEIGHT / 2) - (wall_height / 2);
    end_y = (HEIGHT / 2) + (wall_height / 2);
    begin_x = idx * g->resolution;
    
    draw_ceiling(g, begin_x, begin_y);
    draw_textured_wall(g, idx, begin_x, begin_y, end_y, wall_height);
    // draw_colorful_wall(g, idx, begin_x, begin_y, wall_height);
    draw_floor(g, begin_x, end_y);
}

// !=========================
void    draw_colorful_wall(t_game *g, int idx, int begin_x, int begin_y, int wall_height)
{
    int x;
    int end_y;
    int color;
    t_ray *ray = g->ray + idx;
    
    end_y = begin_y + wall_height;
    while (begin_y <= end_y)
    {
        x = 0;
        while (x < g->resolution)
        {
            color = CYAN;
            if(ray->axis == HORIZONTAL) color = (color >> 1) & 8355711;
            if (!is_outside_window(begin_x + x, begin_y))
                put_pixel_in_image(&g->img_3d, begin_x + x, begin_y, color);
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