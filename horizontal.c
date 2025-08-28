/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:04:36 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/28 11:01:22 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

extern int map[8][8];

void    init_ray_var(t_ray *ray, double ray_angle)
{
    ray->color = RED;
    ray->angle = normalize_angle(ray_angle);
    ray->position = (t_vd){INT_MAX, 0};
    ray->distance = 0;
    ray->hit_wall = false;
    ray->inc = (t_vd){0, 0};
    ray->side = 0;
}

bool    check_win_bound(t_game *g, t_vd position)
{
    if (position.x < 0 || position.x >= g->mapx * g->tilesz)
        return (false);
    if (position.y < 0 || position.y >= g->mapy * g->tilesz)
        return (false);
    return (true);
}

// ! Has problem in this fn
void    increment_to_other_point(t_game *g, t_ray *ray)
{
    while (check_win_bound(g, ray->position))
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
t_ray    horizontal_hit(t_game *g, double ray_angle)
{   
    t_ray ray;

    init_ray_var(&ray, ray_angle);
    //test whether the ray is almost horizontal or almost vertical.
    if (fabs(sin(ray.angle)) < 1e-6) 
        return (printf("        @@@\n"), ray);
    // *: Find the first Intersection Point
    if (FACING_UP(ray.angle))
    {
        ray.position.y = floor(g->ply.position.y / g->tilesz) * g->tilesz - 1e-6;
        ray.inc.y = -g->tilesz;
        ray.side = NORTH;
    }
    else if (FACING_DOWN(ray.angle))
    {
        ray.position.y = floor(g->ply.position.y / g->tilesz) * g->tilesz + g->tilesz;
        ray.inc.y = g->tilesz;
        ray.side = SOUTH;
    }
    else
        printf(TXT_RED"NOT UP OR DOWN !!"RESET);
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

    init_ray_var(&ray, ray_angle);
    // ! Find the first intersection point
    // if (ray.angle == PI / 2 || ray.angle == PI * 3 / 2) // ray_angley is vertical, no intersection
    if (fabs(cos(ray.angle)) < 1e-6)
        return (printf("        ### no!!   ( | )\n"), ray);

    if (FACING_LEFT(ray.angle))
    {
        ray.position.x = floor(g->ply.position.x / g->tilesz) * g->tilesz - 1e-6;
        ray.inc.x = -g->tilesz;
        ray.side = WEST;
    }
    else if (FACING_RIGHT(ray.angle))
    {
        ray.position.x = floor(g->ply.position.x / g->tilesz) * g->tilesz + g->tilesz;
        ray.inc.x = g->tilesz;
        ray.side = EAST;
    }
    else
        printf(TXT_RED"NOT LEFT OR RIGHT !!"RESET);

    ray.position.y = g->ply.position.y + (ray.position.x - g->ply.position.x) * tan(ray.angle);
    ray.inc.y = ray.inc.x * tan(ray.angle);
    
    // * check grid cell at point 'r'
    increment_to_other_point(g, &ray);
    // draw_ray(g->img_2d, g->ply.position, r, BLACK);
    return (ray);
}
