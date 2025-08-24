/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:26 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/24 17:55:01 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
extern int map[8][8];

/*
? Horizontal lines are parallel to the X-axis.
* Vertical   lines are parallel to the Y-axis.
! * handle if no intersections

*/

bool no_intersection(t_vi player, t_vd p)
{
    // if (player.y == INT_MAX && player.x == INT_MAX)
    // {
    //     // printf("-----IS PLLLLLLLLLLLLLLLYER\n", p.x, p.y);
    //     return (true);
    // }
    if (p.x < 0 || p.y < 0)
        return (true);
    if (p.x > WIDTH || p.y > HEIGHT)
    {
        // printf("-----NO INTERSEC  (%.2f , %.2f)\n", p.x, p.y);
        return (1);
    }
    return (false);
}

t_vd    nearest_wall(t_vi player, t_vd w1, t_vd w2)
{
    int ret_1;
    int ret_2;
    
    ret_1 = no_intersection(player, w1);
    ret_2 = no_intersection(player, w2);
    if (ret_1 == true && ret_2 == true)
        return (t_vd){0, 0};
    if (ret_1 == true)
        return w2;
    if (ret_2 == true)
        return w1;
    if (distance(w1, player) < distance(w2, player))
        return (w1);
    return (w2);
}

/*

TODO : WALL-HEIGHT/DIS-TO-WALL  = PROJECTED-WALL-HEIGHT / DIS-TO-PLANE
    ! DIS-TO-PLANE
        *     TAN(FOV/2) = WIDTH / DIS-TO-PLANE
        * <=> DIS-TO-PLANE = WIDTH / TAN(FOV/2)
TODO : SO
    ? PROJECTED-WALL-HEIGHT = DIS-TO-PLANE.(WALL-HEIGHT/DIS-TO-WALL)
*/
// void    draw_wall_3D(t_game *g, t_vd wall)
// {
    
// }
void ray_casting(t_game *g)
{
    t_vd w1 = {WIDTH/2, HEIGHT/2};
    t_vd w2 = {WIDTH/2, HEIGHT/2};
    double  ray_angle;
    double  ray_inc;
    int     ray;
    t_vd    wall;
    
    ray_angle = g->pa - (g->fov / 2);
    ray_inc = g->fov / g->num_rays;
    ray = -1;
    // printf("ply-angle [%.2f]\n", g->pa);
    // printf("fov [%.2f]\n", ((double)g->fov));
    // printf("fov/2 [%.2f]\n", ((double)g->fov / (double)2));
    // printf("ray-angle [%.2f]\n", ray_angle);
    // printf("ray-inc [%.2f]\n", ray_inc);
    
    while (++ray < g->num_rays)
    {
        w1 = horizontal_hit(g, normalize_angle(ray_angle));
        w2 = vertical_hit(g, normalize_angle(ray_angle));
        wall = nearest_wall(g->p, w1, w2);
        // printf("---------INTERSEC COORDINATE [%.2f, %.2f]\n", wall.x, wall.y);
        draw_ray(g->img_2d, g->p, wall, YLW);
        //!aaaaaaaaaaaaaaaaaaaaaaaa
        draw_wall_3d(g, ray, ray_angle, distance(wall, g->p), 0xffffff);
        ray_angle+= ray_inc;
    }
    
}
