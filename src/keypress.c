/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:39:57 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/21 19:25:06 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	check_empty_space(t_vd new_position)
{
	int		index_x;
	int		index_y;
	t_game	*g;

	g = get_addr_t_game(NULL);
	index_x = (new_position.x / g->tilesz);
	index_y = (new_position.y / g->tilesz);
	if (g->map[index_y][index_x] != '1')
	{
		g->ply.position = new_position;
		return (true);
	}
	return (false);
}

void	change_position(int keysym, t_game *g)
{
	t_vd	new_position;

	new_position = g->ply.position;
	if (keysym == XK_w)
	{
		new_position.x += cos(g->ply.angle) * g->ply.move_speed;
		new_position.y += sin(g->ply.angle) * g->ply.move_speed;
	}
	if (keysym == XK_s)
	{
		new_position.x -= cos(g->ply.angle) * g->ply.move_speed;
		new_position.y -= sin(g->ply.angle) * g->ply.move_speed;
	}
	if (keysym == XK_a)
	{
		new_position.x += cos(g->ply.angle - PI / 2) * g->ply.move_speed;
		new_position.y += sin(g->ply.angle - PI / 2) * g->ply.move_speed;
	}
	if (keysym == XK_d)
	{
		new_position.x += cos(g->ply.angle + PI / 2) * g->ply.move_speed;
		new_position.y += sin(g->ply.angle + PI / 2) * g->ply.move_speed;
	}
	check_empty_space(new_position);
}

void	change_angle(int keysym, t_game *g)
{
	if (keysym == XK_Left)
		g->ply.angle = normalize_angle(g->ply.angle - g->ply.rotation_speed);
	if (keysym == XK_Right)
		g->ply.angle = normalize_angle(g->ply.angle + g->ply.rotation_speed);
}

int	keyboard(int keysym, t_game *data)
{
	if (keysym == XK_Escape)
	{
		ft_clean(keysym, data);
		return (0);
	}
	change_position(keysym, data);
	change_angle(keysym, data);
	return (0);
}
