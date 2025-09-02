/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:36 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/02 22:46:05 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[16][16];

bool    is_outside_window(int x, int y)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return (true);
    return (false);
}
void put_pixel_in_image(t_img *image, int x, int y, int col)
{
    int     offset;
    
	if (is_outside_window(x, y))
        return ;
    offset = (y * image->line) + (x * (image->bpp / 8));
    *(unsigned int *)(image->pixels + offset) = col;
}