/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:26 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/22 12:19:50 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int mapx;
extern int mapy;
extern int maps;
extern int map[8][8];

/*
? Horizontal lines are parallel to the X-axis.
* Vertical   lines are parallel to the Y-axis.

! * handle if no intersections
*/


int no_intersection(t_vd p)
{
    if (p.x == -1 && p.y == -1)
        return (1);
    return (0);
}
void cast_rays(t_game *g)
{
    t_vd p1;
    t_vd p2;
    t_vd closest_p;
    
    p1 = horizontal_hit(g, g->pa);
    p2 = vertical_hit(g, g->pa);
    closest_p = p1;
    if (no_intersection(p1) || distance(p1, g->p) > distance(p2, g->p))
        closest_p = p2;
    draw_ray(g->image, g->p, closest_p, YLW);  
}