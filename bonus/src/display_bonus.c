/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:30:11 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/25 12:01:15 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void    draw_big_point(t_img *img, int x, int y,  int r, int col)
{
    for (int dx = -r; dx <= r; dx++)
    {
        for (int dy = -r; dy <= r; dy++)
        {
            if (dx*dx + dy*dy <= r*r)
                put_pixel_in_image(img, x + dx, y + dy, col);
        }
    }
}

int	frames(t_game *game)
{
	static t_ms	last_frame;
	static int	diff;

	diff = 1000 / FPS;
	if (get_time() - last_frame >= diff)
	{
		last_frame = get_time();
		display(game);
	}
	return (0);
}

#define BLUE 0X0000FF
#define GRAY 0X808080
#define RED 0XFF0000

void	minimap_2d(t_game *game)
{
	t_vd center;
	
	center.x = (MINIMAP_W / 2) - 1;
	center.y = (MINIMAP_H / 2) - 1;
	for (int y = 0; y < MINIMAP_H; y++)
	{
		for (int x = 0; x < MINIMAP_W; x++)
		{
			double fx = game->ply.position.x / center.x; 
			double fy = game->ply.position.y / center.y; 
			int tmp_x = (int)(y*fy)/game->tilesz;
			int tmp_y = (int)(x*fx)/game->tilesz;
			if (!(tmp_x < 0 || tmp_y < 0))
			{
				if (game->map[tmp_y][tmp_x] == '1')
					put_pixel_in_image(&game->img_2d, x, y, BLUE);
				else if (game->map[tmp_y][tmp_x] == '0'|| )
					put_pixel_in_image(&game->img_2d, x, y, GRAY);
				else
					put_pixel_in_image(&game->img_2d, x, y, 0xffffff);
			}
		}
	}
	draw_big_point(&game->img_2d, 50, 50, 1, RED);
}

void	display(t_game *g)
{
	ray_casting(g);
	minimap_2d(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img_3d.img, 0, 0);
	mlx_put_image_to_window(g->mlx, g->win, g->img_2d.img, 0, 0);
}
