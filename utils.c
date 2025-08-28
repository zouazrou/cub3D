/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:36 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/28 10:43:37 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int bpp;
extern int line_bytes;
extern int endian;

extern int map[8][8];

void put_pixel_in_image(void *image, int x, int y, int col)
{
    int     offset;
    char    *data_img;
    
    if (x < 0 || y < 0)
        return ;
    data_img = mlx_get_data_addr(image, &bpp, &line_bytes, &endian);
    offset = (y * line_bytes) + (x * (bpp / 8));
    *(int *)(data_img + offset) = col;
    
}



double distance(t_vd p0, t_vd p1)
{
    return (sqrt(pow(p1.x-p0.x, 2) + pow(p1.y-p0.y, 2)));
}

double  deg2rad(int degree)
{
    return (degree * (PI / 180));
}

double  normalize_angle(double radian)
{
    radian = fmod(radian, (PI*2));
    if (radian <  0)
        radian += (PI*2);
    return (radian);
}

bool    is_wall(t_game *g, t_vd position)
{
    if (map[(int)position.y/g->tilesz][(int)position.x/g->tilesz] > 0)
        return (true);
    return (false);
}

void draw_wall_3d(t_game *g, int idx)
{
    int y0;
    int x0;
    int x;
    int y;
    int wall_height_on_screen;
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
    for (y = 0; y < wall_height_on_screen; y++)
    {
        for (x = 0; x < g->resolution; x++)
        {
            if (x0 + x < WIDTH && y0 + y < HEIGHT)
                put_pixel_in_image(g->img_3d, x0 + x, y0 + y, create_rgb(g->ray[idx].color,g->ray[idx].color,g->ray[idx].color));
        }
    }
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

