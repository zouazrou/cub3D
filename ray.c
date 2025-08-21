/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:26 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/20 11:50:15 by zouazrou         ###   ########.fr       */
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
// void draw_ray(t_game *g)
// {
//     int     r = 0;
//     int     mx;
//     int     my;
//     // int     mp;
//     int     dof;
//     float   rx;
//     float   ry;
//     float   ra = 0; // ! ray angle
//     float   xo;
//     float   yo;

//     ra = g->pa;
//     for (r = 0; r < 1; r++)
//     { // ? Check Horizontal Lines '--' "ofoki"
//         dof = 0;
//         float aTan=-1/tan(ra);
//         if (ra > PI) // ! Looking up
//         {
//             ry = (((int)g->p.y>>6)<<6)-0.0001;
//             rx = ((g->p.y -ry))*aTan + g->p.x;
//             yo =-64;
//             xo = -yo*aTan;
//         }
//         if (ra < PI) // ! Looking down
//         {
//             ry = (((int)g->p.y>>6)<<6)+64;
//             rx = ((g->p.y -ry))*aTan + g->p.x;
//             yo = 64;
//             xo = -yo*aTan;
//         }
//         if (ra == 0 || ra == PI)// ! Lonking straight left or right
//         {
//             rx = g->p.x;
//             ry = g->p.y;
//             dof = 1;
//         }
//         int STEPS = mapx;
//         while (dof)
//         {
//             mx = (int)(rx)>>6;
//             my = (int)(ry)>>6;
//             if (map[my][mx] > 0)/* || !((mx > 0 && mx < mapx) && (my > 0 && my < mapy)))*/
//                 dof = 0;
//             else
//             {
//                 rx +=xo;
//                 ry +=yo;
//                 dof++;
//             }
//             // DDA(data->p, (t_vi){data->p.x+data->d.x*17, data->p.y+data->d.y*17}, data);
//         }
//         printf("=--------------before dda\n");
//         DDA(g->p, (t_vi){rx, ry}, g, RED);
//         printf("------------aftre dda\n");
//     }
    
    
// }

void cast_rays(t_game *g)
{
    // t_vd    rd;
    t_vd    r;
    t_vd    inc;
    double ra;

    ra = g->pa;
    /***Find the first intersection point***/
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
    draw_big_point(g->image, (t_vi){(int)r.x, (int)r.y}, 2, RED);
    /***step increments***/
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
    draw_big_point(g->image, (t_vi){(int)r.x + inc.x, (int)r.y + inc.y}, 2, RED);
    

    
    
}