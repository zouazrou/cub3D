/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:20:46 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/02 22:46:02 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[16][16];



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
        radian += (PI*2), printf(TXT_RED"normalize angle fn\n"RESET);
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

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	i;

	i = 0;
	p = malloc((ft_strlen(s) + 1));
	if (p == NULL)
		return (p);
	while (i < ft_strlen(s) + 1)
	{
		*(p + i) = s[i];
		i++;
	}
	return (p);
}
double  fix_fish_eye(t_game *g, int index)
{
    return  (g->ray[index].distance * cos(g->ply.angle - g->ray[index].angle));
}