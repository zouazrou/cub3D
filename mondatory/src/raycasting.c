/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:26 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/25 10:05:50 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	ray_casting(t_game *g)
{
	t_ray	ray_h;
	t_ray	ray_v;
	double	ray_angle;
	int		i;

	i = -1;
	while (++i < g->num_rays)
	{
		ray_angle = g->ply.angle + atan((i - (g->num_rays * 0.5f))
				/ g->distance_to_plane);
		ray_h = horizontal_hit(normalize_angle(ray_angle));
		ray_v = vertical_hit(normalize_angle(ray_angle));
		choose_nearest(g->ray + i, &ray_h, &ray_v);
		draw_3d_view(i);
	}
}
