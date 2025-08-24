/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:04:36 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/24 17:42:49 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

extern int map[8][8];

/*
    ! Horizontal (axix x)
TODO : find first intersection point
    * FACING UP
        ? Ay = floor(Py/tilesz) * tilesz - 1
    * FACING DOWN
        ? Ay = floor(Py/tilesz) * tilesz + tilesz
    ? Ax = (Ay - Py) / tan + Px
    
TODO : Find increment Value
    * FACING UP
        ? Yi = -tilesz
    * FACING DOWN
        ? Yi = tilesz
    ? Xi = Yi / tan
*/
// ! Has problem in this fn
t_vd    horizontal_hit(t_game *g, double ray_angle)
{
    t_vd    r;
    t_vd    inc;

    // *: Find the first Intersection Point
    if (ray_angle == 0 || ray_angle == PI)
        return (printf("        ### no!!   ( -- )\n"), (t_vd){0, INT_MAX});
    if (FACING_UP(ray_angle))
    {
        r.y = (int)(g->p.y / g->tilesz) * g->tilesz - 0.001;
        inc.y = -g->tilesz;
    }
    if (FACING_DOWN(ray_angle))
    {
        r.y = ((int)(g->p.y / g->tilesz)) * g->tilesz + g->tilesz;
        inc.y = g->tilesz;
    }
    r.x = g->p.x + (r.y - g->p.y) / tan(ray_angle);
    inc.x = inc.y / tan(ray_angle);
    
    // *: check grid cell at point 'r'
    bool hit = false;
    while (1)
    {
        if (!check_map_bound(g, r))
            break;
        hit = is_wall(g, r);
        if (hit == true)
            break;
        r.x += inc.x;
        r.y += inc.y;
    }
    // draw_ray(g->img_2d, g->p, r, YLW);  
    return (r);   
}

/*
    ! Vertical (axix x)
TODO : find first intersection point
    * FACING LEFT
        ? Bx = floor(Px/tilesz) * tilesz - 1
    * FACING RIGHT
        ? Bx = floor(Px/tilesz) * tilesz + tilesz
    ? By = Py + (Px - Bx) * tan
    
TODO : Find increment Value
    * FACING LEFT
        ? Xi = -tilesz
    * FACING RIGHT
        ? Xi = tilesz
    ? Yi = Xi * tan
*/
t_vd vertical_hit(t_game *g, double ray_angle)
{
    t_vd r;
    t_vd inc;

    // ! Find the first intersection point
    if (ray_angle == PI / 2 || ray_angle == PI * 3 / 2) // ray_angley is vertical, no intersection
        return (printf("        ### no!!   ( | )\n"), (t_vd){0, INT_MAX});
        // return ((t_vd){-42, -42});
    if (FACING_LEFT(ray_angle))
    {
        r.x = ((int)(g->p.x / g->tilesz)) * g->tilesz - 0.001;
        inc.x = -g->tilesz;
    }
    
    if (FACING_RIGHT(ray_angle))
    {
        r.x = (int)(g->p.x / g->tilesz) * g->tilesz + g->tilesz;
        inc.x = g->tilesz;
        
    }
    r.y = g->p.y + (r.x - g->p.x) * tan(ray_angle);
    inc.y = inc.x * tan(ray_angle);
    // ! check grid cell at point 'r'
    int step = 0;
    int idx_x, idx_y;
    while (check_map_bound(g, r))
    {
        idx_x = (int)(r.x) / g->tilesz;
        idx_y = (int)(r.y) / g->tilesz;
        if (is_wall(g, r))
            break;
        // if (step > g->mapx)
        //     break;
        step++;
        r.x += inc.x;
        r.y += inc.y;
    }
    // draw_ray(g->img_2d, g->p, r, BLACK);
    return (r);
}
