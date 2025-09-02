/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:36 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/02 23:08:20 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[16][16];

bool    is_outside_window(t_game *g, int x, int y)
{
    if (x < 0 || x >= g->width || y < 0 || y >= g->height)
        return (true);
    return (false);
}
void put_pixel_in_image(t_game *g, t_img *image, int x, int y, int col)
{
    int     offset;
    
	if (is_outside_window(g, x, y))
        return ;
    offset = (y * image->line) + (x * (image->bpp / 8));
    *(unsigned int *)(image->pixels + offset) = col;
}