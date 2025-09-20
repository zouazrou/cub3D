/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:36 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/20 15:32:06 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool    is_outside_window(int x, int y)
{
    t_game *g;

    g = get_addr_t_game(NULL);
    if (x < 0 || x >= g->width || y < 0 || y >= g->height)
        return (true);
    return (false);
}
void put_pixel_in_image(int x, int y, int col)
{
    int     offset;
    t_game *g;
    
    g = get_addr_t_game(NULL);
	if (is_outside_window(x, y))
        return ;
    offset = (y * g->img_3d.line) + (x * (g->img_3d.bpp / 8));
    *(unsigned int *)(g->img_3d.pixels + offset) = col;
}

t_game *get_addr_t_game(t_game *ptr)
{
    static t_game *addr = NULL;

    if (ptr)
        addr = ptr;
    return (addr);
}