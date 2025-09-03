/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:04:36 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/03 09:27:06 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

extern int map[8][8];

void    init_ray_var(t_ray *ray, double ray_angle)
{
    ray->color = 255;
    ray->angle = normalize_angle(ray_angle);
    ray->inter = (t_vd){INT_MAX, 0};
    ray->distance = 0;
    ray->hit_wall = false;
    ray->inc = (t_vd){0, 0};
    ray->side = 0;
    ray->axis = 0;
}

bool    check_win_bound(t_game *g, t_vd position)
{
    if (position.x < 0 || position.x >= g->mapx * g->tilesz)
        return (false);
    if (position.y < 0 || position.y >= g->mapy * g->tilesz)
        return (false);
    return (true);
}

void    increment_to_the_wall(t_game *g, t_ray *ray)
{
    while (check_win_bound(g, ray->inter))
    {
        if (is_wall(g, ray->inter) == true)
        {
            ray->hit_wall = true;
            break;
        }
        ray->inter.x += ray->inc.x;
        ray->inter.y += ray->inc.y;
    }
    ray->distance = distance(ray->inter, g->ply.position);
}

t_ray    horizontal_hit(t_game *g, double ray_angle)
{   
    t_ray ray;

    init_ray_var(&ray, ray_angle);
    ray.axis = HORIZONTAL;
    if (fabs(sin(ray.angle)) < 1e-6) 
        return (printf("        @@@\n"), ray);
    if (facing_up(ray.angle))
    {
        ray.inter.y = floor(g->ply.position.y / g->tilesz) * g->tilesz - 1e-6;
        ray.inc.y = -g->tilesz;
        ray.side = NORTH;
    }
    if (facing_down(ray.angle))
    {
        ray.inter.y = floor(g->ply.position.y / g->tilesz) * g->tilesz + g->tilesz;
        ray.inc.y = g->tilesz;
        ray.side = SOUTH;
    }
    ray.inter.x = g->ply.position.x + (ray.inter.y - g->ply.position.y) / tan(ray.angle);
    ray.inc.x = ray.inc.y / tan(ray.angle);
    increment_to_the_wall(g, &ray);
    return (ray);   
}

t_ray vertical_hit(t_game *g, double ray_angle)
{
    t_ray ray;

    init_ray_var(&ray, ray_angle);
    ray.axis = VERTICAL;
    if (fabs(cos(ray.angle)) < 1e-6)
        return (printf("        ### no!!   ( | )\n"), ray);
    if (facing_left(ray.angle))
    {
        ray.inter.x = floor(g->ply.position.x / g->tilesz) * g->tilesz - 1e-6;
        ray.inc.x = -g->tilesz;
        ray.side = WEST;
    }
    if (facing_right(ray.angle))
    {
        ray.inter.x = floor(g->ply.position.x / g->tilesz) * g->tilesz + g->tilesz;
        ray.inc.x = g->tilesz;
        ray.side = EAST;
    }
    ray.inter.y = g->ply.position.y + (ray.inter.x - g->ply.position.x) * tan(ray.angle);
    ray.inc.y = ray.inc.x * tan(ray.angle);
    increment_to_the_wall(g, &ray);
    return (ray);
}
