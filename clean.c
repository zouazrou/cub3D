/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:32:19 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/28 08:32:26 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_clean(t_game *g, bool ter)
{
    free(g->ray);

    // mlx_destroy_window(g->mlx, g->win_2d);
    mlx_destroy_window(g->mlx, g->win_3d);
    // mlx_destroy_image(g->mlx, g->img_2d);
    mlx_destroy_image(g->mlx, g->img_3d);
    mlx_destroy_display(g->mlx);
    free(g->mlx);
    if (ter == true)
        exit(EXIT_SUCCESS);
}