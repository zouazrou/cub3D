/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:04:36 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/21 11:23:04 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	row_len(const char *row)
{
	int	i;

	i = 0;
	if (!row)
		return (0);
	while (row[i] && row[i] != '\n')
		i++;
	return (i);
}

bool	check_win_bound(t_ray *ray)
{
	int		x;
	int		y;
	int		width;
	t_game	*g;

	g = get_addr_t_game(NULL);
	x = (int)(ray->inter.x / g->tilesz);
	y = (int)(ray->inter.y / g->tilesz);
	if (y < 0 || y >= g->mapy)
		return (false);
	width = row_len(g->map[y]);
	if (x < 0 || x >= width)
		return (false);
	return (true);
}

void	increment_to_the_wall(t_ray *ray)
{
	t_game	*g;

	g = get_addr_t_game(NULL);
	while (check_win_bound(ray))
	{
		if (is_wall(ray) == true)
			break ;
		ray->inter.x += ray->inc.x;
		ray->inter.y += ray->inc.y;
	}
	ray->distance = distance(ray->inter, g->ply.position);
}

t_ray	horizontal_hit(double ray_angle)
{
	t_ray	ray;
	t_game	*g;

	g = get_addr_t_game(NULL);
	init_ray_struct(&ray, ray_angle);
	ray.axis = HORIZONTAL;
	if (fabs(sin(ray.angle)) < 1e-6)
		return (ray);
	if (facing_up(ray.angle))
	{
		ray.inter.y = (int)(g->ply.position.y / g->tilesz) * g->tilesz - 1e-6;
		ray.inc.y = -g->tilesz;
		ray.side = NORTH;
	}
	else if (facing_down(ray.angle))
	{
		ray.inter.y = (int)(g->ply.position.y / g->tilesz) * g->tilesz
			+ g->tilesz;
		ray.inc.y = g->tilesz;
		ray.side = SOUTH;
	}
	ray.inter.x = g->ply.position.x + (ray.inter.y - g->ply.position.y)
		/ tan(ray.angle);
	ray.inc.x = ray.inc.y / tan(ray.angle);
	return (increment_to_the_wall(&ray), ray);
}

t_ray	vertical_hit(double ray_angle)
{
	t_ray	ray;
	t_game	*g;

	g = get_addr_t_game(NULL);
	init_ray_struct(&ray, ray_angle);
	ray.axis = VERTICAL;
	if (fabs(cos(ray.angle)) < 1e-6)
		return (ray);
	if (facing_left(ray.angle))
	{
		ray.inter.x = floor(g->ply.position.x / g->tilesz) * g->tilesz - 1e-6;
		ray.inc.x = -g->tilesz;
		ray.side = WEST;
	}
	else if (facing_right(ray.angle))
	{
		ray.inter.x = floor(g->ply.position.x / g->tilesz) * g->tilesz
			+ g->tilesz;
		ray.inc.x = g->tilesz;
		ray.side = EAST;
	}
	ray.inter.y = g->ply.position.y + (ray.inter.x - g->ply.position.x)
		* tan(ray.angle);
	ray.inc.y = ray.inc.x * tan(ray.angle);
	return (increment_to_the_wall(&ray), ray);
}
