/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:26 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/25 10:58:15 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
extern int map[8][8];

/*
? Horizontal lines are parallel to the X-axis.
* Vertical   lines are parallel to the Y-axis.
! * handle if no intersections

*/


// bool no_intersection(t_vi player, t_vd p)
// {
//     // if (player.y == INT_MAX && player.x == INT_MAX)
//     // {
//     //     // printf("-----IS PLLLLLLLLLLLLLLLYER\n", p.x, p.y);
//     //     return (true);
//     // }
//     if (p.x < 0 || p.y < 0)
//         return (true);
//     if (p.x > WIDTH || p.y > HEIGHT)
//     {
//         // printf("-----NO INTERSEC  (%.2f , %.2f)\n", p.x, p.y);
//         return (1);
//     }
//     return (false);
// }

// t_vd    nearest_wall(t_game *g, t_vd w1, t_vd w2)
// {
//     int ret_1;
//     int ret_2;
//     t_vi player = g->ply.position;
    
//     ret_1 = no_intersection(player, w1);
//     ret_2 = no_intersection(player, w2);
//     if (ret_1 == true && ret_2 == true)
//         return (t_vd){0, 0};
//     if (ret_1 == true)
//         return w2;
//     // if (ret_2 == true)
//     //     return (g->ray_color = 160, w1);
//     // if (distance(w1, player) < distance(w2, player))
//     //     return (g->ray_color = 160, w1);
//     return (w2);
// }

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
    t_ray   ray_h;
    t_ray   ray_v;
    double  ray_angle;
    double  ray_inc;
    int     idx;
    
    ray_angle = g->ply.angle - (g->fov / 2);
    ray_inc = g->fov / g->num_rays;
    idx = -1;
    // printf("ply-angle [%.2f]\n", g->pa);
    // printf("fov [%.2f]\n", ((double)g->fov));
    // printf("fov/2 [%.2f]\n", ((double)g->fov / (double)2));
    // printf("ray-angle [%.2f]\n", ray_angle);
    // printf("ray-inc [%.2f]\n", ray_inc);
    
    while (++idx < g->num_rays)
    {
        ray_h = horizontal_hit(g, ray_angle);
        ray_v = vertical_hit(g, ray_angle);
        if (ray_h.hit_wall && !ray_v.hit_wall)
        {
            g->ray[idx] = ray_h;
            g->ray[idx].color = GREEN;
        }
        else if (!ray_h.hit_wall && ray_v.hit_wall)
        {
            g->ray[idx] = ray_v;
            g->ray[idx].color = GREEN;
        }
        else if (ray_h.hit_wall && ray_v.hit_wall)
        {
            if (ray_h.distance < ray_v.distance)
            {
                g->ray[idx] = ray_h;
                g->ray[idx].color = WHITE;
            }
            else
            {
                g->ray[idx] = ray_v;
                g->ray[idx].color = WHITE;
            }
        }
        else
        {

            printf("-------ERROR-------ray num [%d] CHI 7AAAJA MAHIYACH HAN !!\n", idx);
        }
        // printf("---------INTERSEC COORDINATE [%.2f, %.2f]\n", wall.x, wall.y);
        draw_ray(g->img_2d, g->ply.position, g->ray[idx].position, YLW);
        //!aaaaaaaaaaaaaaaaaaaaaaaa
        draw_wall_3d(g, idx);
        ray_angle+= ray_inc;
    }
    
}
