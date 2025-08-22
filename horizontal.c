/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:04:36 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/22 12:20:06 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

extern int mapx;
extern int mapy;
extern int maps;
extern int map[8][8];

t_vd    horizontal_hit(t_game *g, double ray_angle)
{
    t_vd    r;
    t_vd    inc;

    // ! Find the first intersectiontion point
    if (ray_angle == 0 || ray_angle == PI) // ray_angley is horizontal, no intersectiontion
    {
        // r.x = g->p.x;
        // r.y = g->p.y;
        // inc.x = 0;
        // inc.y = 0;
        return ((t_vd){-42, -42});
    }
    if (ray_angle > PI && ray_angle < 2 * PI) // facing up
    {
        r.y = ((int)(g->p.y / 64)) * 64 - 1;
        r.x = g->p.x + (r.y - g->p.y) / tan(ray_angle);
        inc.y = -64;
        inc.x = inc.y / tan(ray_angle);
    }
 
    if (ray_angle > 0 && ray_angle < PI) // facing down
    {
        r.y = ((int)(g->p.y / 64)) * 64 + 64;
        r.x = g->p.x + (r.y - g->p.y) / tan(ray_angle);
        inc.y = 64;
        inc.x = inc.y / tan(ray_angle);
    }
    // ! check grid cell at point 'r'
    int step = 0;
    int idx_x, idx_y;
    while (1)
    {
        idx_x = (int)(r.x) / 64;
        idx_y = (int)(r.y) / 64;
        if (!check_map(idx_x, idx_y) || map[idx_y][idx_x] != 0)
            break;
        if (step > mapx)
            break;
        step++;
        r.x += inc.x;
        r.y += inc.y;
    }
    // draw_ray(g->image, g->p, r, YLW);  
    return (r);   
}

t_vd vertical_hit(t_game *g, double ray_angle)
{
    t_vd r;
    t_vd inc;

    // ! Find the first intersection point
    if (ray_angle == PI / 2 || ray_angle == PI * 3 / 2) // ray_angley is vertical, no intersection
    {
        // r.x = g->p.x;
        // r.y = g->p.y;
        // inc.x = 0;
        // inc.y = 0;
        return ((t_vd){-42, -42});
    }
    if (ray_angle > PI / 2 && ray_angle < PI * 3 / 2) // facing left
    {
        r.x = ((int)(g->p.x / 64)) * 64 - 1;
        r.y = g->p.y + (r.x - g->p.x) * tan(ray_angle);
        inc.x = -64;
        inc.y = inc.x * tan(ray_angle);
    }
    
    if (ray_angle < PI / 2 || ray_angle > PI * 3 / 2) // facing right
    {
        r.x = ((int)(g->p.x / 64)) * 64 + 64;
        r.y = g->p.y + (r.x - g->p.x) * tan(ray_angle);
        inc.x = 64;
        inc.y = inc.x * tan(ray_angle);
    }

    // ! check grid cell at point 'r'
    int step = 0;
    int idx_x, idx_y;
    while (1)
    {
        idx_x = (int)(r.x) / 64;
        idx_y = (int)(r.y) / 64;
        if (!check_map(idx_x, idx_y) || map[idx_y][idx_x] != 0)
            break;
        if (step > mapx)
            break;
        step++;
        r.x += inc.x;
        r.y += inc.y;
    }
    // draw_ray(g->image, g->p, r, BLACK);
    return (r);
}
