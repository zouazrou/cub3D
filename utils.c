/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:36 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/30 09:40:26 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int bpp;
extern int line_bytes;
extern int endian;
extern int map[8][8];

bool    is_outside_window(int x, int y)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return (printf(TXT_BLUE"OUTSIDE !!\n\n"RESET), true);
    return (false);
}



int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

