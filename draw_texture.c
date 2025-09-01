/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 10:55:28 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/01 08:17:46 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int    get_pixel_color(t_texture *texture, int x, int y)
{
    int offset;

    if (x < 0 || x >= texture->w)
    {
        printf(TXT_BLUE"get_pxl_color()\n"RESET);
        return (0);
    }
    
    if (y < 0 || y >= texture->h)
    {
        printf(TXT_BLUE"get_pxl_color()\n"RESET);
        return (0);
    }
    offset = (y * texture->line) + (x * (texture->bpp / 8));
    return ((*(unsigned int *)(texture->pixels + offset))& 0x00FFFFFF);
}

// * This calculates which column (x-coordinate) of the texture to use:
int calculate_tex_x(t_game *g, t_ray *ray, t_texture *texture)
// ! side = 0 => Vertical
// ! side = 1 => Horizontal
{
    double wall_x;
    int tex_x;
    
    if (ray->axis == HORIZONTAL)
        wall_x = g->ply.position.x + ray->distance * cos(ray->angle);
    else if (ray->axis == VERTICAL)
        wall_x = g->ply.position.y + ray->distance * sin(ray->angle);
    else
        printf("debug: not H nor V !!\n");
    
    wall_x -= floor(wall_x);
    tex_x = (int)(wall_x * (double)texture->w);
    
    // Adjust for texture orientation
    if ((ray->axis == VERTICAL && cos(ray->angle) < 0) ||
        (ray->axis == HORIZONTAL && sin(ray->angle) > 0))
        tex_x = texture->w - tex_x - 1;
    
    return (tex_x);
}

void    draw_textured_wall(t_game *g, int idx, int begin_x, int begin_y, int end_y, int wall_height)
{
    int x;
    int y;
    int color;
    int tex_x;
    int tex_y;
    double tex_step;
    double tex_pos;
    t_ray *ray = g->ray + idx;
    t_texture *texture = &g->west; // TMP
    
    tex_x = calculate_tex_x(g, ray, texture);
    tex_step = (double)texture->h / wall_height;
    tex_pos = (begin_y - (HEIGHT/2.0) + wall_height/2.0) * tex_step;


    
    y = begin_y;
    while (y < end_y)
    {
        tex_y = tex_pos;
        if (tex_y < 0)
        {
            printf("WAAAAAAAAAAAH\n");
            tex_y = 0;
        }
        if (tex_y >= texture->h)
        {
            printf("WAAAAAAAAAAAH\n");
            tex_y = texture->h - 1;
        }
        tex_pos += tex_step;
        
        // Get color from texture
        color = get_pixel_color(texture, tex_x, tex_y);
        x = 0;
        while (x < g->resolution)
            put_pixel_in_image(g->img_3d, begin_x + x++, y, color);
        y++;
    }
}