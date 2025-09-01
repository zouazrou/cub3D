/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:32:19 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/01 11:23:18 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_clean(int keysym, t_game *g)
{
    if (keysym != XK_Escape)
        return (0);
    free(g->ray);
    mlx_destroy_window(g->mlx, g->win_3d);
    mlx_destroy_image(g->mlx, g->img_3d.img);
    mlx_destroy_display(g->mlx);
    free(g->mlx);
    exit(EXIT_SUCCESS);
}