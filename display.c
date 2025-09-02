/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:30:11 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/02 21:53:29 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    display(t_game *g)
{

    ray_casting(g);
    printf(TXT_BLUE"Ply [%.2f:%.2f]\n"RESET, g->ply.position.x/g->tilesz, g->ply.position.y/g->tilesz);
    // ? Player
    mlx_put_image_to_window(g->mlx, g->win_3d, g->img_3d.img, 0, 0);
}