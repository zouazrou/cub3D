/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:30:11 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/21 21:27:25 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	frames(t_game *game)
{
	static t_ms	last_frame;
	static int	diff;

	diff = 1000 / FPS;
	if (get_time() - last_frame >= diff)
	{
		last_frame = get_time();
		printf("ply[%.2f:%.2f]\n", game->ply.position.x, game->ply.position.y);
		display(game);
		printf(TXT_CYAN "\n============\n" RESET);
	}
	return (0);
}

void	display(t_game *g)
{
	ray_casting(g);
	mlx_put_image_to_window(g->mlx, g->win_3d, g->img.img, 0, 0);
}
