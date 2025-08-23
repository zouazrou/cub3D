/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:36 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/23 20:17:04 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int bpp;
extern int line_bytes;
extern int endian;

extern int map[8][8];

void put_pixel_in_image(void *image, int x, int y, int col)
{
    int     offset;
    char    *data_img;
    
    if (x < 0 || y < 0)
        return ;
    data_img = mlx_get_data_addr(image, &bpp, &line_bytes, &endian);
    offset = (y * line_bytes) + (x * (bpp / 8));
    *(int *)(data_img + offset) = col;
    
}

bool    check_map_bound(t_game *g, t_vd position)
{
    int x;
    int y;
    
    x = (int)(position.x) / g->tilesz;
    y = (int)(position.y) / g->tilesz;
    if (x < 0 || x >= g->mapx || y < 0 || y >= g->mapy)
        return (false);
    return (true);
}

int distance(t_vd p0, t_vi p1)
{
    // printf("dis = %.2f", sqrt(pow(p0.x-p1.x, 2) + pow(p0.y-p1.y, 2)));
    return (sqrt(pow(p1.x-p0.x, 2) + pow(p1.y-p0.y, 2)));
    // return (sqrt((p1.x-p0.x)*(p1.x-p0.x)+(p1.y-p0.y)*(p1.y-p0.y)));
}

double  deg_to_rad(int degree)
{
    return (degree * PI /180);
}

double  normalize_angle(double radian)
{
    radian = fmod(radian, (PI*2));
    if (radian <  0)
        radian += (PI*2);
    return (radian);
}

bool    is_wall(t_game *g, t_vd position)
{
    int idx_x;
    int idx_y;
    
    idx_x = (int)(position.x) / g->tilesz;
    idx_y = (int)(position.y) / g->tilesz;
    if (map[idx_y][idx_x] > 0)
        return (true);
    return (false);
}

bool    FACING_DOWN(double angle)
{
    if (angle > 0 && angle < PI)
        return (true);
    return (false);
}

bool    FACING_UP(double angle)
{
    // if (angle > PI && angle < 2 * PI)
    //     return (true);
    // return (false);
    return (!FACING_DOWN(angle));
}

bool    FACING_RIGHT(double angle)
{
    if (angle < PI / 2 || angle > PI * 3 / 2)
        return (true);
    return (false);
}

bool    FACING_LEFT(double angle)
{
    // if (angle > PI / 2 && angle < PI * 3 / 2)
    //     return (true);
    // return (false);
    return (!FACING_RIGHT(angle)); 
}