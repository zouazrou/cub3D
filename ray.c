/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:26 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/23 21:39:18 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>
extern int map[8][8];

/*
? Horizontal lines are parallel to the X-axis.
* Vertical   lines are parallel to the Y-axis.
! * handle if no intersections

*/

int no_intersection(t_vi player, t_vd p)
{
    if (player.y == INT_MAX && player.x == INT_MAX)
    {
        printf("-----IS PLLLLLLLLLLLLLLLYER\n", p.x, p.y);
        return (1);
    }
    if (p.x < 0 || p.y < 0 || p.x > WIDTH || p.y > HEIGHT)
    {
        printf("-----NO INTERSEC  (%.2f , %.2f)\n", p.x, p.y);
        return (1);
    }
    return (0);
}

t_vd    nearest_wall(t_vi player, t_vd w1, t_vd w2)
{
    int ret_1;
    int ret_2;
    
    ret_1 = no_intersection(player, w1);
    ret_2 = no_intersection(player, w2);
    if (ret_1 && ret_2)
        return (t_vd){0, 0};
    if (ret_1)
        return w2;
    if (ret_2)
        return w1;
    if (distance(w1, player) < distance(w2, player))
        return (w1);
    return (w2);
}

void ray_casting(t_game *g)
{
    t_vd w1 = {WIDTH/2, HEIGHT/2};
    t_vd w2 = {WIDTH/2, HEIGHT/2};
    double  ray_angle;
    double  ray_inc;
    int     num_rays;
    t_vd    wall;
    
    ray_angle = g->pa - (g->fov / 2);
    ray_inc = g->fov / g->num_rays;
    num_rays = g->num_rays;
    // printf("ply-angle [%.2f]\n", g->pa);
    // printf("fov [%.2f]\n", ((double)g->fov));
    // printf("fov/2 [%.2f]\n", ((double)g->fov / (double)2));
    // printf("ray-angle [%.2f]\n", ray_angle);
    // printf("ray-inc [%.2f]\n", ray_inc);
    while (num_rays--)
    {
        w1 = horizontal_hit(g, normalize_angle(ray_angle));
        w2 = vertical_hit(g, normalize_angle(ray_angle));
        wall = nearest_wall(g->p, w1, w2);
        draw_ray(g->image, g->p, wall, YLW);
        ray_angle+= ray_inc;
    }
    
}
