/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:20:46 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/25 10:05:50 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	distance(t_vd p0, t_vd p1)
{
	return (sqrt(pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2)));
}

double	deg2rad(int degree)
{
	return (degree * (PI / 180));
}

double	normalize_angle(double radian)
{
	radian = fmod(radian, (PI * 2));
	if (radian < 0)
		radian += (PI * 2);
	return (radian);
}

double	fix_fish_eye(int index)
{
	t_game	*g;

	g = get_addr_t_game(NULL);
	return (g->ray[index].distance * cos(g->ply.angle - g->ray[index].angle));
}
