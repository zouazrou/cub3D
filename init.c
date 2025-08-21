/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:27:15 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/21 23:37:01 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int bpp;
extern int line_bytes;
extern int endian;
extern int tilex;
extern int tiley;

void    init_data(t_game *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, W, H, "small game");
    data->image = mlx_new_image(data->mlx, W, H);
    // ? angle by rad
    // data->pa = (PI)*1/3;
    // data->pa = (PI*3/2) + (PI/4); //  degree
    data->pa = (PI) + (PI/4); //  degree
    // ? convert angle to vector
    data->d.x = cos(data->pa);
    data->d.y = sin(data->pa);
    printf("debug: angle [%f]>>dx[%f]>>dy[%f]\n\n", data->pa, data->d.x, data->d.y);
    
    data->p.x = 5.5 * 64;
    data->p.y = 3.5 * 64;
    data->sp = 5;
    data->fov = 60;
    data->plane.x = 0;
    data->plane.y = 0.66;
}


void    draw_big_point(void *img, int x, int y,  int r, int col)
{
    char *data_img = mlx_get_data_addr(img, &bpp, &line_bytes, &endian);
    for (int dx = -r; dx <= r; dx++)
    {
        for (int dy = -r; dy <= r; dy++)
        {
            if (dx*dx + dy*dy <= r*r) // inside circle
                put_pixel_in_image(img, x + dx, y + dy, col);
        }
    }
}
/*

x->
Y|>
            pi*4/3
            |
            |
            |
            |
            |
pi--------------------0
            |          <
            |
            |
            |
            pi/2
*/