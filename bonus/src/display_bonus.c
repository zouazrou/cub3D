/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:30:11 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/24 18:52:34 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

void	display(t_game *g)
{
	ray_casting(g);
	mlx_put_image_to_window(g->mlx, g->win_3d, g->img.img, 0, 0);
}
