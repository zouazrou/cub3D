/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:48 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/21 10:05:45 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    DDA(t_vi a, t_vi b, t_game *data, int col)
{
	int		dx;
    int		dy;
	double	Xinc, Yinc;
	double	x, y;
    int		steps;


    // printf("Xp0 = %d | Yp0 = %d\nXb = %d | Yb = %d\n", p0.x, p0.y, b.x, b.y);
    //
    dx = b.x - a.x;
    dy = b.y - a.y;
    // printf("Xd = %d | Yd = %d\n", dx, dy);

    // steps 
    steps = abs(dx);
    if (abs(dx) < abs(dy))
        steps = abs(dy);
    // calculate increment in x & y for each steps
    Xinc = (double)(dx / (double)steps);
    Yinc = (double)(dy / (double)steps);
    // printf("Xinc = %f | Yinc = %f\n", Xinc, Yinc);

    // draw line in the window
    x = a.x;
	y = a.y;
    // printf("x = %.2f | y = %.2f\n", x, y);
    int flg = 0;
    for (int i = 0; i <= steps; i++)
    {
        // put pixel in this position ...
		// !mlx_pixel_put(data->mlx, data->win, x, y, 0xFFFFFF);
        draw_big_point(data->image, x, y, 1, col);
        x += Xinc;
        y += Yinc;
        if (flg == 0)
        {
            printf("x = %f | y = %f\n", x, y);
            flg++;
        }
    }
}