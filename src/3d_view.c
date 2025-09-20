/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_view.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 09:40:07 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/20 17:41:05 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_ceiling(int begin_x, int begin_y)
{
	int		x;
	int		y;
	t_game	*g;

	g = get_addr_t_game(NULL);
	y = -1;
	while (++y < begin_y)
	{
		x = -1;
		while (++x < g->resolution)
			put_pixel_in_image(begin_x + x, y, g->ceiling_color);
	}
}

void	draw_floor(int begin_x, int begin_y)
{
	int		x;
	int		y;
	t_game	*g;

	g = get_addr_t_game(NULL);
	y = begin_y - 1;
	while (++y < g->height)
	{
		x = -1;
		while (++x < g->resolution)
			put_pixel_in_image(begin_x + x, y, g->floor_color);
	}
}

void	draw_3d_view(int idx)
{
	int		begin_x;
	int		begin_y;
	int		end_y;
	int		wall_height;
	t_game	*g;

	g = get_addr_t_game(NULL);
	g->ray[idx].distance = fix_fish_eye(idx);
	wall_height = (g->tilesz * g->distance_to_plane) / g->ray[idx].distance;
	begin_y = (g->height / 2) - (wall_height / 2);
	end_y = (g->height / 2) + (wall_height / 2);
	begin_x = idx * g->resolution;
	draw_ceiling(begin_x, begin_y);
	draw_cube(idx, begin_y, end_y, wall_height);
	draw_floor(begin_x, end_y);
}

t_ms	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((t_ms)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

int	frames(t_game *data)
{
	static t_ms	last_frame;
	static int	diff;

	diff = 1000 / FPS;
	if (get_time() - last_frame >= diff)
	{
		last_frame = get_time();
		display(data);
		printf(TXT_CYAN "\n============\n" RESET);
	}
	return (0);
}
// void    draw_colorful_cube(int idx, int begin_x, int begin_y,
		// int wall_height)
// {
//     int x;
//     int end_y;
//     int color;
//     t_ray *ray = g->ray + idx;

//     end_y = begin_y + wall_height;
//     while (begin_y <= end_y)
//     {
//         x = 0;
//         while (x < g->resolution)
//         {
//             color = CYAN;
//             if(ray->axis == HORIZONTAL) color = (color >> 1) & 8355711;
//             put_pixel_in_image(g, begin_x + x, begin_y, color);
//             x++;
//         }
//         begin_y++;
//     }
// }
