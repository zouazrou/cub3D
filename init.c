/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:27:15 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/17 21:19:35 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_data(t_game *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, W, H, "dda");
    data->dir.x = -1;
    data->dir.y = 0;
    data->pos.x = 100;
    data->pos.y = 100;
    data->plane.x = 0;
    data->plane.y = 0.66;
}


void    mlx_big_point(t_game *data, int r, int color)
{
    for (int dx = -r; dx <= r; dx++)
    {
        for (int dy = -r; dy <= r; dy++)
        {
            if (dx*dx + dy*dy <= r*r) // inside circle
                mlx_pixel_put(data->mlx, data->win, data->pos.x + dx, data->pos.y + dy, color);
        }
    }
}
int  close_win(void *ptr)
{
    printf("Exit !\n");
    exit(0);
}
int keyboard(int keysym, t_game *data)
{
    if (keysym == XK_Escape)
		exit((printf("Exit ! (esc)"), 0));
	else if (keysym == XK_Up || keysym == XK_w)
        data->pos.y -= 25;		
    else if (keysym == XK_Down || keysym == XK_s)
        data->pos.y += 25;		
    else if (keysym == XK_Left || keysym == XK_a)
        data->pos.x -= 25;		
    else if (keysym == XK_Right || keysym == XK_d)
        data->pos.x += 25;	
    	
	return (0);   
}