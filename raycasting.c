/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:26 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/02 22:25:07 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
extern int map[16][16];

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
        *ray = *ray_h;
    else if (!ray_h->hit_wall && ray_v->hit_wall)
        *ray = *ray_v;
    else if (ray_h->hit_wall && ray_v->hit_wall)
    {
        if (ray_h->distance < ray_v->distance)
            *ray = *ray_h;
        else
            *ray = *ray_v;
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
    int     i;
    
    ray_angle = g->ply.angle - (g->fov / 2);
    ray_inc = g->fov / g->num_rays;
    i = -1;
    while (++i < g->num_rays)
    {
        ray_h = horizontal_hit(g, normalize_angle(ray_angle));
        ray_v = vertical_hit(g, normalize_angle(ray_angle));
        choose_nearest(g->ray + i, &ray_h, &ray_v, i);
        
        int col = WHITE;
        if (g->ray[i].side == NORTH)
            col = RED;
        if (g->ray[i].side == SOUTH)
            col = GREEN;
        if (g->ray[i].side == EAST)
            col = BROWN;
        if (g->ray[i].side == WEST)
            col = YLW;
        draw_3d_view(g, i);
        ray_angle+= ray_inc;
    }
}
