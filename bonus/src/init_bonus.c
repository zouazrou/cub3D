/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:27:15 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/30 15:00:49 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	init_ray(t_game *g)
{
	g->ray = ft_calloc(g->num_rays, sizeof(t_ray));
	if (!g->ray)
		ft_clean(-1, g);
}

void	init_screen(t_game *g)
{
	g->resolution = 1;
	g->tilesz = 10;
	g->num_rays = g->width / g->resolution;
	g->fov = deg2rad(60);
	g->distance_to_plane = (g->width / 2.0) / (tan(g->fov / 2.0));
}

void	init_player(t_game *g)
{
	g->ply.move_speed = 0.1 * g->tilesz;
	g->ply.rotation_speed = deg2rad(2);
}

void	init_minilibx(t_game *g)
{
	bool	error;

	error = false;
	g->mlx = mlx_init();
	if (!g->mlx && true)
		error = true;
	init_textures(get_addr_t_data(NULL));
	g->win = mlx_new_window(g->mlx, g->width, g->height, "3D");
	g->img_2d.img = mlx_new_image(g->mlx, MINIMAP_W, MINIMAP_H);
	g->img_2d.pixels = mlx_get_data_addr(g->img_2d.img, &g->img_2d.bpp,
			&g->img_2d.line, &g->img_2d.endian);
	g->img_3d.img = mlx_new_image(g->mlx, g->width, g->height);
	g->img_3d.pixels = mlx_get_data_addr(g->img_3d.img, &g->img_3d.bpp,
			&g->img_3d.line, &g->img_3d.endian);
	if (!g->win || !g->img_2d.img || !g->img_3d.img
		|| !g->img_3d.pixels || !g->img_2d.pixels)
		error = true;
	if (error == true)
	{
		ft_perror(NULL);
		ft_clean(-1, g);
	}
}

void	init_game(t_game *g)
{
	ft_bzero(g, sizeof(t_game));
	get_addr_t_game(g);
	g->width = WIDTH;
	g->height = HEIGHT;
	init_screen(g);
	init_player(g);
	init_ray(g);
}
