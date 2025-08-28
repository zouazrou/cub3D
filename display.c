/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:30:11 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/29 00:45:35 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[8][8];
extern int bpp;
extern int line_bytes;
extern int endian;

void drow_quade(t_game *g, int x0, int y0, int col)
{
    for (int y = 0; y < g->tilesz; y++)
    {
        for (int x = 0; x < g->tilesz; x++)
        {
            if (!y || !x || y == g->tilesz-1 || y == g->tilesz-1)
                put_pixel_in_image(g->img_2d, x0 + x, y0 + y, BLACK);
            else
                put_pixel_in_image(g->img_2d, x0 + x, y0 + y, col);
        }
    }
}

void    draw_map2D(t_game *g)
{
    for (int y = 0; y < g->mapy; y++)
    {
        for (int x = 0; x < g->mapx; x++)
        {
            if (map[y][x] == 1)
                drow_quade(g, x * g->tilesz, y * g->tilesz, BLCK_SHDW);
            if (map[y][x] == 0)
                drow_quade(g, x * g->tilesz, y * g->tilesz, BLUE);
        }
    }

}
void fill_img(void *img, int col, int h, int w)
{
    // printf("debug : fill_img()\n");
    // printf("bpp = %d| line_bytes = %d| endian=  %d\n", bpp, line_bytes, endian);
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
            put_pixel_in_image(img, x, y, col);
    }
}
void draw_dir(t_game *g, int len, int color)
{
    // compute end point
    float x2 = g->ply.position.x + cos(g->ply.angle) * len;
    float y2 = g->ply.position.y + sin(g->ply.angle) * len;

    float dx = x2 - g->ply.position.x;
    float dy = y2 - g->ply.position.y;

    int steps = fabs(dy);
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);

    float x_inc = dx / steps;
    float y_inc = dy / steps;

    float x = g->ply.position.x;
    float y = g->ply.position.y;

    for (int i = 0; i <= steps; i++)
    {
        // // if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        // //     break;
        put_pixel_in_image(g->img_2d, (int)x, (int)y, color);
        // printf("dir ply : x = %d ====== y = %d\n", (int)x, (int)y);
        x += x_inc;
        y += y_inc;
        
    }
}

void draw_ray(void *img, t_vd p0, t_vd p1, int color)
{
    // compute end point
    t_vd    d;
    t_vd    inc;
    
    d.x = p1.x - p0.x;
    d.y = p1.y - p0.y;

    int steps = fabs(d.y);
    if (fabs(d.x) > fabs(d.y))
        steps = fabs(d.x);

    inc.x = d.x / steps;
    inc.y = d.y / steps;

    float x = p0.x;
    float y = p0.y;

    for (int i = 0; i <= steps; i++)
    {
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
            break;
        put_pixel_in_image(img, (int)x, (int)y, color);
        // draw_big_point(img, (int)x, (int)y, 1, color);
        // printf("ray : x = %d ====== y = %d\n", (int)x, (int)y);
        x += inc.x;
        y += inc.y;
    }
}

void    display(t_game *g)
{

    // printf("debug : draw_map2D()\n");
    // ? Map
    
    // ? Ray-Casting
    fill_img(g->img_2d, 0x30302e, HEIGHT, WIDTH);
    fill_img(g->img_3d, 0x0, HEIGHT, WIDTH);
    draw_map2D(g);
    ray_casting(g);
    // printf(TXT_BLUE"Ply [%.2f:%.2f]\n"RESET, g->ply.position.x, g->ply.position.y);
    draw_big_point(g->img_2d, g->ply.position.x, g->ply.position.y, g->tilesz/10, RED);
    draw_dir(g, g->tilesz/4, RED);
    // ? Player
    mlx_put_image_to_window(g->mlx, g->win_3d, g->img_3d, 0, 0);
    mlx_put_image_to_window(g->mlx, g->win_2d, g->img_2d, 0, 0);
}