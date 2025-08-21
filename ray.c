/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:26 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/22 00:00:57 by zouazrou         ###   ########.fr       */
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

int check_map(int x, int y)
{
    if (x < 0 || x >= mapx || y < 0 || y >= mapy)
        return (0);
    return (1);
}
void    check_Horizontal(t_game *g)
{
    t_vd    r;
    t_vd    inc;
    float ra;

    ra = g->pa;
    // ! Find the first intersection point
    if (ra == 0 || ra == PI) // Ray is horizontal, no intersection
    {
        r.x = g->p.x;
        r.y = g->p.y;
        inc.x = 0;
        inc.y = 0;
    }
    else if (ra > PI && ra < 2 * PI) // facing up
    {
        r.y = ((int)(g->p.y / 64)) * 64 - 0.0001;
        r.x = g->p.x + (r.y - g->p.y) / tan(ra);
        inc.y = -64;
        inc.x = inc.y / tan(ra);
    }
    else if (ra > 0 && ra < PI) // facing down
    {
        r.y = ((int)(g->p.y / 64)) * 64 + 64;
        r.x = g->p.x + (r.y - g->p.y) / tan(ra);
        inc.y = 64;
        inc.x = inc.y / tan(ra);
    }
    // printf("                A.x = %.1f | A.y = %.1f\n", r.x/64, r.y/64);
    // printf("               inc-x %.1f | in-y %.1f\n", (inc.x), (inc.y));
    // printf("                A.x = %.1f | A.y = %.1f\n", (r.x+inc.x)/64, (r.y+inc.y)/64);
    // ! check grid cell at point 'r'
    int step = 0;
    int map_x, map_y;
    while (1)
    {
        map_x = (int)(r.x) / 64;
        map_y = (int)(r.y) / 64;
        if (!check_map(map_x, map_y))
            break;
        if (map[map_y][map_x] != 0)
            break;
        step++;
        r.x += inc.x;
        r.y += inc.y;
    }

    printf("inc-x = %.2f ||| inc-x = %.2f\n", inc.x, inc.y);
    printf("wall ==> x = %.1f --------- y = %.1f\nstep = %d\n", r.x, r.y, step);
    printf("plyr ==> x = %.1f --------- y = %.1f\n", g->p.x, g->p.y);
    draw_ray(g->image, g->p, r, BROWN);
}

void    check_vertical(t_game *g)
{
    t_vd    r;
    t_vd    inc;
    float ra;

    ra = g->pa;
    // ! Find the first intersection point
    if (ra > PI/2 && ra < (PI*3)/2)            // facing left
    {
        r.x = ((int)(g->p.x/64))*64 - 0.0001;
        r.y = g->p.y + (g->p.x - r.x)*tan(ra);
        inc.x = -64;
        inc.y = inc.x*tan(ra);
    }
    else if (ra < PI/2 || ra > (PI*3)/2)   // facing right
    {
        r.x = ((int)(g->p.x/64))*64 + 64;
        r.y = g->p.y + (g->p.x - r.x)*tan(ra);
        inc.x = 64;
        inc.y = inc.x*tan(ra);
    }
    if (ra == PI/2 || ra == (PI*3)/2) 
    {
        r.x = g->p.x;
        r.y = g->p.y;
    }
    // ! check grid cell at point 'r'
    int step = 0;
    while (check_map(r.x/64, r.y/64))
    {
        if (map[(int)r.y/64][(int)r.x/64] != 0)
            break;
        step++;
        r.x += inc.x;
        r.y += inc.y;
    }
    
    draw_ray(g->image, g->p, r, RED);
}


void cast_rays(t_game *g)
{
    check_Horizontal(g);
    check_vertical(g);
}