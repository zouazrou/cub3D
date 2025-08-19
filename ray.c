/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:26 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/19 10:33:51 by zouazrou         ###   ########.fr       */
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
void draw_ray(t_game *g)
{
    int     r = 0;
    int     mx;
    int     my;
    // int     mp;
    int     dof;
    float   rx;
    float   ry;
    float   ra = 0; // ! ray angle
    float   xo;
    float   yo;

    ra = g->pa;
    for (r = 0; r < 1; r++)
    { // ? Check Horizontal Lines '--' "ofoki"
        dof = 0;
        float aTan=-1/tan(ra);
        if (ra > PI) // ! Looking up
        {
            ry = (((int)g->p.y>>6)<<6)-0.0001;
            rx = ((g->p.y -ry))*aTan + g->p.x;
            yo =-64;
            xo = -yo*aTan;
        }
        if (ra < PI) // ! Looking down
        {
            ry = (((int)g->p.y>>6)<<6)+64;
            rx = ((g->p.y -ry))*aTan + g->p.x;
            yo = 64;
            xo = -yo*aTan;
        }
        if (ra == 0 || ra == PI)// ! Lonking straight left or right
        {
            rx = g->p.x;
            ry = g->p.y;
            dof = 1;
        }
        int STEPS = mapx;
        while (dof)
        {
            mx = (int)(rx)>>6;
            my = (int)(ry)>>6;
            if (map[my][mx] > 0)/* || !((mx > 0 && mx < mapx) && (my > 0 && my < mapy)))*/
                dof = 0;
            else
            {
                rx +=xo;
                ry +=yo;
                dof++;
            }
            // DDA(data->p, (t_vi){data->p.x+data->d.x*17, data->p.y+data->d.y*17}, data);
        }
        printf("=--------------before dda\n");
        DDA(g->p, (t_vi){rx, ry}, g, RED);
        printf("------------aftre dda\n");
    }
    
    
}

void draw_rayv2(t_game *g)
{
    for (int r = 0; r < W; r++)
    {
        t_vd rd;
        double camera_x;
        
        camera_x = 2 * r / (double)W -1; // x-coordinate in camera space
        rd.x = g->d.x + g->plane.x * camera_x;
        rd.y = g->d.y + g->plane.y * camera_x;
    }
    
}