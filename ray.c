/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:26 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/28 11:10:55 by zouazrou         ###   ########.fr       */
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
    int     i;
    
    ray_angle = g->ply.angle - (g->fov / 2);
    ray_inc = g->fov / g->num_rays;
    i = -1;
    // printf("ply-angle [%.2f]\n", g->pa);
    // printf("fov [%.2f]\n", ((double)g->fov));
    // printf("fov/2 [%.2f]\n", ((double)g->fov / (double)2));
    // printf("ray-angle [%.2f]\n", ray_angle);
    // printf("ray-inc [%.2f]\n", ray_inc);
    
    while (++i < g->num_rays)
    {
        ray_h = horizontal_hit(g, normalize_angle(ray_angle));
        ray_v = vertical_hit(g, normalize_angle(ray_angle));
        printf("\n[%d]\n", i);
        printf("Horizontal wall [%.2f: %.2f]\n", ray_h.position.x, ray_h.position.y);
        printf("vertical   wall [%.2f: %.2f]\n", ray_v.position.x, ray_v.position.y);
        choose_nearest(g->ray + i, &ray_h, &ray_v,    i);
        printf("nearest    wall [%.2f: %.2f]\n", g->ray[i].position.x, g->ray[i].position.y);
        
        int col = WHITE;
        if (g->ray[i].side == NORTH)
            col = RED;
        // printf(TXT_RED"RAY\n"RESET);
        if (g->ray[i].side == SOUTH)
            col = GREEN;
        // printf(TXT_BLUE"RAY\n"RESET);
        if (g->ray[i].side == EAST)
            col = BROWN;
        // printf(TXT_MAGENTA"RAY\n"RESET);
        if (g->ray[i].side == WEST)
            col = YLW;
        // printf(TXT_GREEN"RAY\n"RESET);
        // draw_ray(g->img_2d, g->ply.position, g->ray[i].position, col);
        // draw_ray(g->img_2d, g->ply.position, g->ray[i].position, g->ray[i].color);
        //!aaaaaaaaaaaaaaaaaaaaaaaa
        draw_wall_3d(g, i);
        ray_angle+= ray_inc;
    }
    
}
