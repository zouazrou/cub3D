/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:39:57 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/22 13:31:55 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#define DIST 0.2
bool	check_empty_space(t_vd new)
{
	t_game	*g;
	t_vd	possible_wall;
	double dx[4] = {1, -1, 0,  0};
	double dy[4] = {0,  0, 1, -1};
	

	g = get_addr_t_game(NULL);
	possible_wall.x = (new.x / (double)g->tilesz);
	possible_wall.y = (new.y / (double)g->tilesz);
	for (int i = 0; i < 4; i++)
	{
		if (g->map[(int)(possible_wall.y + (dy[i]*DIST))][(int)(possible_wall.x + (dx[i]*DIST))] == '1')
		{
			printf(TXT_BLUE"You must leave 0.2 btw the Player and the WAll !\n"RESET);
			return (false);
		}
	}
	if (g->map[(int)possible_wall.y][(int)possible_wall.x] != '1')
	{
		g->ply.position = new;
		return (true);
	}
	
	return (false);
}

void	change_position(int keysym, t_game *g)
{
	t_vd	new;

	new = g->ply.position;
	if (keysym == XK_w)
	{
		new.x += cos(g->ply.angle) * g->ply.move_speed;
		new.y += sin(g->ply.angle) * g->ply.move_speed;
	}
	if (keysym == XK_s)
	{
		new.x -= cos(g->ply.angle) * g->ply.move_speed;
		new.y -= sin(g->ply.angle) * g->ply.move_speed;
	}
	if (keysym == XK_a)
	{
		new.x += cos(g->ply.angle - PI / 2) * g->ply.move_speed;
		new.y += sin(g->ply.angle - PI / 2) * g->ply.move_speed;
	}
	if (keysym == XK_d)
	{
		new.x += cos(g->ply.angle + PI / 2) * g->ply.move_speed;
		new.y += sin(g->ply.angle + PI / 2) * g->ply.move_speed;
	}
	check_empty_space(new);
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
