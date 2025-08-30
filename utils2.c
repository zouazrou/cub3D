/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:20:46 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/30 09:41:10 by zouazrou         ###   ########.fr       */
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

double distance(t_vd p0, t_vd p1)
{
    return (sqrt(pow(p1.x-p0.x, 2) + pow(p1.y-p0.y, 2)));
}

double  deg2rad(int degree)
{
    return (degree * (PI / 180));
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
    if (map[(int)position.y/g->tilesz][(int)position.x/g->tilesz] > 0)
        return (true);
    return (false);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*buf;
	size_t			i;

	i = 0;
	buf = (unsigned char *)s;
	while (i < n)
	{
		buf[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = malloc(nmemb * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return (p);
}

double  fix_fish_eye(t_game *g, int index)
{
    return  (g->ray[index].distance * cos(g->ply.angle - g->ray[index].angle));
}