/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:27:15 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/23 20:57:19 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int bpp;
extern int line_bytes;
extern int endian;

void    init_data(t_game *g)
{
    // ? MAP & MLX
    g->mapx = 8;
    g->mapy = 8;
    g->mlx = mlx_init();
    g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "small game");
    g->image = mlx_new_image(g->mlx, WIDTH, HEIGHT);
    

    
    // ? screen setting
    g->resolution = 16;
    g->tilesz = 64;
    // g->num_rays = 6; // ! TMP
    g->num_rays = WIDTH / g->resolution;
    g->move_speed = g->tilesz/10;
    if (g->tilesz < 10)
        g->move_speed = 1;
    g->rotation_speed = deg_to_rad(3);
    g->fov = deg_to_rad(60);
    // g->plane.x = 0;
    // g->plane.y = 0.66;

    // ? Player's Postion
    g->p.x = (4) * g->tilesz;
    g->p.y = (4) * g->tilesz;
    
    // ? angle by rad
    g->pa = deg_to_rad(180);
    
    // ? convert angle to vector
    g->d.x = cos(g->pa);
    g->d.y = sin(g->pa);
    // printf("debug: angle [%f]>>dx[%f]>>dy[%f]\n\n", g->pa, g->d.x, g->d.y);
}


void    draw_big_point(void *img, int x, int y,  int r, int col)
{
    for (int dx = -r; dx <= r; dx++)
    {
        for (int dy = -r; dy <= r; dy++)
        {
            if (dx*dx + dy*dy <= r*r) // inside circle
                put_pixel_in_image(img, x + dx, y + dy, col);
        }
    }
}
/*

x->
Y|>
            pi*4/3
            |
            |
            |
            |
            |
pi--------------------0
            |          <
            |
            |
            |
            pi/2
*/