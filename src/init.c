/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:27:15 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/20 17:39:34 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_ray(t_game *g)
{
	g->ray = ft_calloc(g->num_rays, sizeof(t_ray));
	if (!g->ray)
		exit((perror("malloc()"), 1));
}

void	init_screen(t_game *g)
{
	g->resolution = 1;
	g->tilesz = 1;
	g->num_rays = g->width / g->resolution;
	g->fov = deg2rad(60);
	g->distance_to_plane = (g->width / 2.0) / (tan(g->fov / 2.0));
	printf(TXT_GREEN "RAYS NUM -> %d" RESET "\n", g->num_rays);
}

void	init_player(t_game *g)
{
	g->ply.move_speed = 0.1 * g->tilesz;
	g->ply.rotation_speed = deg2rad(3);
	g->ply.position.x = (20) * g->tilesz;
	g->ply.position.y = (7.5) * g->tilesz;
	g->ply.angle = deg2rad(270);
}

void	init_minilibx(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		exit((perror("mlx_int()"), 1));
	g->win_3d = mlx_new_window(g->mlx, g->width, g->height, "3D");
	if (!g->win_3d)
		exit((perror("mlx_new_window()"), 42));
	g->img.img = mlx_new_image(g->mlx, g->width, g->height);
	if (!g->img.img)
		exit((perror("mlx_new_image()"), 42));
	g->img.pixels = mlx_get_data_addr(g->img.img, &g->img.bpp, &g->img.line,
			&g->img.endian);
	if (!g->img.pixels)
		exit((perror("mlx_get_data_addr()"), 42));
}

void	init_game(t_game *g)
{
	ft_bzero(g, sizeof(t_game));
	get_addr_t_game(g);
	g->width = WIDTH;
	g->height = HEIGHT;
	g->ceiling_color = LIGHT_BLUE;
	g->floor_color = DARK_GRAY;
	init_screen(g);
	init_player(g);
	init_ray(g);
	init_minilibx(g);
}

/*
? Wall-Height / dis-to-the-Wall
!            == 
? Projected-Wall-Height / dis-ply-to-projection-plane  


*/