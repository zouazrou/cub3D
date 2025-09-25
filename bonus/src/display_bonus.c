/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:30:11 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/25 10:59:38 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

void	minimap_2d(t_game *game)
{
	int x;
	int y;
	
	
	for (y = 0; y < MINIMAP_H; y++)
	{
		for (x = 0; x < MINIMAP_W; x++)
		{
			
			put_pixel_in_image(&game->img_2d, x, y, 0xffffff);
		}
	}
}

void	display(t_game *g)
{
	ray_casting(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img_3d.img, 0, 0);
}
