/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:36 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/24 18:27:59 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_outside_window(int x, int y)
{
	t_game	*g;

	g = get_addr_t_game(NULL);
	if (x < 0 || x >= g->width || y < 0 || y >= g->height)
		return (true);
	return (false);
}

void	put_pixel_in_image(int x, int y, int col)
{
	int		offset;
	t_game	*g;

	g = get_addr_t_game(NULL);
	if (is_outside_window(x, y))
		return ;
	offset = (y * g->img.line) + (x * (g->img.bpp / 8));
	*(unsigned int *)(g->img.pixels + offset) = col;
}

t_game	*get_addr_t_game(t_game *ptr)
{
	static t_game	*addr = NULL;

	if (ptr)
		addr = ptr;
	return (addr);
}

void	init_ray_struct(t_ray *ray, double ray_angle)
{
	ray->color = 255;
	ray->angle = normalize_angle(ray_angle);
	ray->inter = (t_vd){INT_MAX, 0};
	ray->distance = 0;
	ray->hit_wall = false;
	ray->inc = (t_vd){0, 0};
	ray->side = 0;
	ray->axis = 0;
}

bool	is_wall(t_ray *ray)
{
	int		x;
	int		y;
	t_game	*g;

	g = get_addr_t_game(NULL);
	x = (int)ray->inter.x / g->tilesz;
	y = (int)ray->inter.y / g->tilesz;
	if (g->map[y][x] == ' ' || g->map[y][x] == '\n')
		return (true);
	if (g->map[y][x] == '1')
	{
		ray->hit_wall = true;
		return (true);
	}
	return (false);
}
