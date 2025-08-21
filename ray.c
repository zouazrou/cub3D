/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:26 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/21 14:15:13 by zouazrou         ###   ########.fr       */
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
*/

void cast_rays(t_game *g)
{
    // t_vd    rd;
    t_vd    r;
    t_vd    inc;
    double ra;

    ra = g->pa;
    // ! Find the first intersection point
    if (ra < PI )   // facing down
    {
        r.y = (g->p.y/64)*64-1;
        r.x = g->p.x + ((g->p.y - r.y)/tan(ra));
    }
    else if (ra > PI)            // facing up
    {
        r.y = (g->p.y/64)*64+64;
        r.x = g->p.x + ((g->p.y - r.y)/tan(ra));
    }
    else
    {
        r.x = g->p.x;
        r.y = g->p.y;
    }
    // draw_big_point(g->image, r.x, r.y, 2, RED);
    // ! step increments
    if (ra < PI) // facing down
    {
        inc.y = -64;
        inc.x = 64/tan(ra);
    }
    else if (ra > PI)
    {
        inc.y = 64;
        inc.x = 64/tan(ra);
    }
    // draw_big_point(g->image, r.x, r.y, 2, RED);
    // draw_big_point(g->image, r.x + inc.x, r.y + inc.y, 3, RED);
    // ! check grid cell at point 'r'
    int step = 0;
    while (map[(int)r.y/64][(int)r.y/64] == 0)
    {
        step++;
        r.x += inc.x;
        r.y += inc.y;
    }
    printf("inc-x = %.2f ||| inc-x = %.2f\n", inc.x, inc.y);
    printf("wall ==> x = %d --------- y = %d\nstep = %d\n", r.x, r.y, step);
    printf("plyr ==> x = %d --------- y = %d\n", g->p.x, g->p.y);
    draw_ray(g->image, g->p, r, GREEN);
    // draw_big_point(g->image, (int)r.x, (int)r.y, 4, RED);
}