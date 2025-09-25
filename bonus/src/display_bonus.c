/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:30:11 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/25 20:51:44 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	draw_big_point(t_img *img, int x, int y, int r)
{
	int	dx;
	int	dy;

	dx = -r - 1;
	while (++dx <= r)
	{
		dy = -r - 1;
		while (++dy <= r)
		{
			if (dx * dx + dy * dy <= r * r)
				put_pixel_in_image(img, x + dx, y + dy, RED);
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

void	minimap_2d(t_game *g)
{
	double	i;
	double	j;
	t_vd	m;
	t_vd	d;

	j = -1;
	while (++j < MINIMAP_H)
	{
		i = -1;
		while (++i < MINIMAP_W)
		{
			d.x = i - (MINIMAP_W / 2.0);
			d.y = j - (MINIMAP_H / 2.0);
			m.x = (int)((g->ply.position.x) + d.x) / g->tilesz;
			m.y = (int)((g->ply.position.y) + d.y) / g->tilesz;
			if (m.y < 0 || m.y >= g->mapy || !g->map[(int)m.y] || m.x < 0
				|| m.x >= (int)ft_strlen(g->map[(int)m.y]))
				put_pixel_in_image(&g->img_2d, i, j, GRAY);
			else if (g->map[(int)m.y][(int)m.x] == '1')
				put_pixel_in_image(&g->img_2d, i, j, BLUE);
			else
				put_pixel_in_image(&g->img_2d, i, j, GRAY);
		}
	}
	draw_big_point(&g->img_2d, MINIMAP_W / 2, MINIMAP_H / 2, 3);
}

void	display(t_game *g)
{
	ray_casting(g);
	minimap_2d(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img_3d.img, 0, 0);
	mlx_put_image_to_window(g->mlx, g->win, g->img_2d.img, 0, 0);
}
