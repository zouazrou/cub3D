/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:39:57 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/25 10:05:50 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_directions(double dx[5], double dy[5])
{
	dx[0] = 0;
	dx[1] = 0.2;
	dx[2] = -0.2;
	dx[3] = 0;
	dx[4] = 0;
	dy[0] = 0;
	dy[1] = 0;
	dy[2] = 0;
	dy[3] = 0.2;
	dy[4] = -0.2;
}

void	check_valid_move(t_vd new)
{
	int		i;
	t_game	*g;
	double	dx[5];
	double	dy[5];
	t_vd	possible_wall;

	g = get_addr_t_game(NULL);
	init_directions(dx, dy);
	possible_wall.x = (new.x / (double)g->tilesz);
	possible_wall.y = (new.y / (double)g->tilesz);
	i = -1;
	while (++i < 5)
	{
		if (g->map[(int)(possible_wall.y + dy[i])]
			[(int)(possible_wall.x + dx[i])] == '1')
			return ;
	}
	g->ply.position = new;
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
	check_valid_move(new);
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
