/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:04:36 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/25 11:02:11 by zouazrou         ###   ########.fr       */
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
void    increment_to_other_point(t_game *g, t_ray *ray)
{
    while (check_map_bound(g, ray->position))
    {
        if (is_wall(g, ray->position) == true)
        {
            ray->hit_wall = true;
            break;
        }
        ray->position.x += ray->inc.x;
        ray->position.y += ray->inc.y;
    }
    ray->distance = distance(ray->position, g->ply.position);
}
t_ray    horizontal_hit(t_game *g, double ray_angle)
{   
    t_ray ray;

    ray.angle = normalize_angle(ray_angle);
    // *: Find the first Intersection Point
    if (ray.angle == 0 || ray.angle == PI)
        return (printf("        @@@\n"), (t_ray){0});
    if (FACING_UP(ray.angle))
    {
        ray.position.y = (int)(g->ply.position.y / g->tilesz) * g->tilesz - 0.0001;
        ray.inc.y = -g->tilesz;
    }
    if (FACING_DOWN(ray.angle))
    {
        ray.position.y = (int)(g->ply.position.y / g->tilesz) * g->tilesz + g->tilesz;
        ray.inc.y = g->tilesz;
    }
    ray.position.x = g->ply.position.x + (ray.position.y - g->ply.position.y) / tan(ray.angle);
    ray.inc.x = ray.inc.y / tan(ray.angle);
    
    // *: check grid cell at point 'r'
    increment_to_other_point(g, &ray);
    
    // draw_ray(g->img_2d, g->ply.position, r, YLW);  
    return (ray);   
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
t_ray vertical_hit(t_game *g, double ray_angle)
{
    t_ray ray;

    ray.angle = normalize_angle(ray_angle);
    // ! Find the first intersection point
    if (ray.angle == PI / 2 || ray.angle == PI * 3 / 2) // ray_angley is vertical, no intersection
        return (printf("        ### no!!   ( | )\n"), (t_ray){0});
    if (FACING_LEFT(ray.angle))
    {
        ray.position.x = (int)(g->ply.position.x / g->tilesz) * g->tilesz - 0.0001;
        ray.inc.x = -g->tilesz;
    }
    if (FACING_RIGHT(ray.angle))
    {
        ray.position.x = (int)(g->ply.position.x / g->tilesz) * g->tilesz + g->tilesz;
        ray.inc.x = g->tilesz;
    }
    ray.position.y = g->ply.position.y + (ray.position.x - g->ply.position.x) * tan(ray.angle);
    ray.inc.y = ray.inc.x * tan(ray.angle);
    
    // * check grid cell at point 'r'
    increment_to_other_point(g, &ray);
    // draw_ray(g->img_2d, g->ply.position, r, BLACK);
    return (ray);
}
