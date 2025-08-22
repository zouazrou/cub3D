/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:36 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/22 12:18:13 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int bpp;
extern int line_bytes;
extern int endian;

extern int mapx;
extern int mapy;
extern int maps;
extern int map[8][8];

void put_pixel_in_image(void *image, int x, int y, int col)
{
    int     offset;
    char    *data_img;

    data_img = mlx_get_data_addr(image, &bpp, &line_bytes, &endian);
    offset = (y * line_bytes) + (x * (bpp / 8));
    *(int *)(data_img + offset) = col;
    
}

int check_map(int x, int y)
{
    if (x < 0 || x >= mapx || y < 0 || y >= mapy)
        return (0);
    return (1);
}

int distance(t_vd p0, t_vi p1)
{
    printf("dis = %.2f", sqrt(pow(p0.x-p1.x, 2) + pow(p0.y-p1.y, 2)));
    return (sqrt(pow(p0.x-p1.x, 2) + pow(p0.y-p1.y, 2)));
}