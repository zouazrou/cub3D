/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:27:15 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/18 21:19:49 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int bpp;
extern int line_bytes;
extern int endian;

void    init_data(t_game *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, W, H, "small game");
    data->image = mlx_new_image(data->mlx, W, H);
    // angle
    data->pa = PI;
    data->d.x = cos(data->pa);
    data->d.y = sin(data->pa);
    data->p.x = 200;
    data->p.y = 300;
    data->sp = 5;
    data->plane.x = 0;
    data->plane.y = 0.66;
}


void    draw_big_point(void *img, t_vi crd, int r, int col)
{
    char *data_img = mlx_get_data_addr(img, &bpp, &line_bytes, &endian);
    for (int dx = -r; dx <= r; dx++)
    {
        for (int dy = -r; dy <= r; dy++)
        {
            if (dx*dx + dy*dy <= r*r) // inside circle
                put_pixel_in_image(img, crd.x + dx, crd.y + dy, col);
        }
    }
}
