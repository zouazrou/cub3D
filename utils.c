/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:36 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/28 23:57:42 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int bpp;
extern int line_bytes;
extern int endian;
extern int map[8][8];


void    draw_ceiling(t_game *g, double x0, double max_y)
{
    double x;
    double y;

    for (y = 0; y < max_y; y++)
    {
        for (x = 0; x < g->resolution; x++)
        {
            // if (check_bound_map())
                put_pixel_in_image(g->img_3d, x0+x, y, BLUE);
        }
    }
}

void    draw_floor(t_game *g, double x0,double y0)
{
    double x;
    double y;

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < g->resolution; x++)
        {
            // if (check_bound_map())
                put_pixel_in_image(g->img_3d, x0+x, y0+y, DARK_GRAY);
        }
    }
}
void    draw_floor(t_game *g, double x0,double y0);

void draw_wall_3d(t_game *g, int idx)
{
    double y0;
    double x0;
    double x;
    double y;
    double wall_height_on_screen;
    t_ray *r;

    r = g->ray + idx;
    
    // ? fix fish eye 
    r->distance *= cos(g->ply.angle - r->angle) ;
    /****LIGHT*****/
    // r->color *= (LIGHT_LVL / r->distance);
    // if (r->color < 0)
    //     r->color = 0;
    // if (r->color > 255)
    //     r->color = 255;
    /*********/
    wall_height_on_screen = (g->tilesz * g->distance_to_plane) / r->distance;
    x0 = idx * g->resolution;
    y0 = (HEIGHT/2) - (wall_height_on_screen/2);
    if (y0 < 0)
        y0 = 0;
    if (wall_height_on_screen >= HEIGHT)
        wall_height_on_screen = HEIGHT-1;
    
    draw_ceiling(g, x0, y0);
    for (y = 0; y < wall_height_on_screen; y++)
    {
        for (x = 0; x < g->resolution; x++)
        {
            if (x0 + x < WIDTH && y0 + y < HEIGHT)
                put_pixel_in_image(g->img_3d, x0 + x, y0 + y, create_rgb(g->ray[idx].color,g->ray[idx].color,g->ray[idx].color));
        }
    }
    draw_floor(g, x0, y0 + y);
}



int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

