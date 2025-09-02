/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 10:55:28 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/02 23:09:46 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture *select_texture(t_game *g, t_ray *ray)
{
    if (ray->side == WEST)
        return (&g->west);
    if (ray->side == NORTH)
        return (&g->north);
    if (ray->side == SOUTH)
        return (&g->south );
    if (ray->side == EAST)
        return (&g->east);
    return (NULL);
}

unsigned int    get_pixel_color(t_texture *texture, int x, int y)
{
    int offset;

    if (x < 0 || x >= texture->w || y < 0 || y >= texture->h)
    {
        printf(TXT_BLUE"get_pxl_color()\n"RESET);
        return (0);
    }
    
    offset = (y * texture->image.line) + (x * (texture->image.bpp / 8));
    return ((*(unsigned int *)(texture->image.pixels + offset))& 0x00FFFFFF);
}

int calculate_tex_x(t_game *g, t_ray *ray, t_texture *texture)
{
    int tex_x;
    double wall_x;
    
    if (ray->axis == HORIZONTAL)
        wall_x = ray->inter.x;
    else
        wall_x = ray->inter.y;
    
    wall_x -= floor(wall_x / g->tilesz) * g->tilesz;
    tex_x = (int)(wall_x / g->tilesz * texture->w);
    
    if ((ray->axis == VERTICAL && cos(ray->angle) < 0) ||
        (ray->axis == HORIZONTAL && sin(ray->angle) > 0)) // ! KHASK TBDLHA !!
    {
        printf("waaah\n");
        tex_x = texture->w - tex_x - 1;
    }
    return (tex_x);
}


// static void    draw_wall
void    draw_cube(t_game *g, int idx, int begin_x, int begin_y, int end_y, int wall_height)
{
    int     color;
    int     x;
    int     y;
    int     tex_x;
    int     tex_y;
    double  tex_step;
    double  tex_pos;
    t_ray *ray = g->ray + idx;
    t_texture *texture;
    
    texture = select_texture(g, ray);
    tex_x = calculate_tex_x(g, ray, texture);
    tex_step = (double)texture->h / wall_height;
    tex_pos = (begin_y - g->height/2.0 + wall_height/2.0) * tex_step;
    y = begin_y-1;
    while (++y < end_y)
    {
        tex_y = (int)tex_pos & (texture->h - 1);
        tex_pos += tex_step;
        color = get_pixel_color(texture, tex_x, tex_y);
        x = -1;
        while (++x < g->resolution)
            put_pixel_in_image(g, &g->img_3d, begin_x + x, y, color);
    }
}
