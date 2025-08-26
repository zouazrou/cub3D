/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:26 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/26 11:57:29 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
extern int map[8][8];

/*
? Horizontal lines are parallel to the X-axis.
* Vertical   lines are parallel to the Y-axis.


TODO : WALL-HEIGHT/DIS-TO-WALL  = PROJECTED-WALL-HEIGHT / DIS-TO-PLANE
    ! DIS-TO-PLANE
        *     TAN(FOV/2) = WIDTH / DIS-TO-PLANE
        * <=> DIS-TO-PLANE = WIDTH / TAN(FOV/2)
TODO : SO
    ? PROJECTED-WALL-HEIGHT = DIS-TO-PLANE.(WALL-HEIGHT/DIS-TO-WALL)
*/

void    choose_nearest(t_ray *ray, t_ray *ray_h, t_ray *ray_v, int index)
{
    if (ray_h->hit_wall && !ray_v->hit_wall)
    {
        *ray = *ray_h;
        ray->color = 160;
    }
    else if (!ray_h->hit_wall && ray_v->hit_wall)
    {
        *ray = *ray_v;
        ray->color = 255;
    }
    else if (ray_h->hit_wall && ray_v->hit_wall)
    {
        if (ray_h->distance < ray_v->distance)
        {
            *ray = *ray_h;
            ray->color = 160;
        }
        else
        {
            *ray = *ray_v;
            ray->color = 255;
        }
    }
    else
        printf(TXT_RED"-------ERROR-------ray num [%d] CHI 7AAAJA MAHIYACH HAN !!\n"RESET, index);
}

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
        choose_nearest(g->ray + idx, &ray_h, &ray_v,    idx);
        int col = WHITE;
        if (g->ray[idx].side == NORTH)
            col = RED;
        // printf(TXT_RED"RAY\n"RESET);
        if (g->ray[idx].side == SOUTH)
            col = GREEN;
        // printf(TXT_BLUE"RAY\n"RESET);
        if (g->ray[idx].side == EAST)
            col = BROWN;
        // printf(TXT_MAGENTA"RAY\n"RESET);
        if (g->ray[idx].side == WEST)
            col = YLW;
        // printf(TXT_GREEN"RAY\n"RESET);
        draw_ray(g->img_2d, g->ply.position, g->ray[idx].position, col);
        // draw_ray(g->img_2d, g->ply.position, g->ray[idx].position, g->ray[idx].color);
        //!aaaaaaaaaaaaaaaaaaaaaaaa
        draw_wall_3d(g, idx);
        ray_angle+= ray_inc;
    }
    
}
