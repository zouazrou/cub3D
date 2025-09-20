/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:29 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/20 17:40:57 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	hooks(t_game *data)
{
	mlx_hook(data->win_3d, DestroyNotify, 0, ft_clean, NULL);
	mlx_hook(data->win_3d, KeyPress, KeyPressMask, keyboard, data);
	mlx_loop_hook(data->mlx, frames, data);
}

void	convert_xpm_to_images(void)
{
	t_game	*g;

	g = get_addr_t_game(NULL);
	g->north.image.img = mlx_xpm_file_to_image(g->mlx, g->north.filename,
			&g->north.w, &g->north.h);
	g->south.image.img = mlx_xpm_file_to_image(g->mlx, g->south.filename,
			&g->south.w, &g->south.h);
	g->west.image.img = mlx_xpm_file_to_image(g->mlx, g->west.filename,
			&g->west.w, &g->west.h);
	g->east.image.img = mlx_xpm_file_to_image(g->mlx, g->east.filename,
			&g->east.w, &g->east.h);
	if (!g->north.image.img || !g->south.image.img || !g->west.image.img
		|| !g->east.image.img)
		exit((perror("mlx_xpm_file_to_image()"), 1));
	g->north.image.pixels = mlx_get_data_addr(g->north.image.img,
			&g->north.image.bpp, &g->north.image.line, &g->north.image.endian);
	g->south.image.pixels = mlx_get_data_addr(g->south.image.img,
			&g->south.image.bpp, &g->south.image.line, &g->south.image.endian);
	g->west.image.pixels = mlx_get_data_addr(g->west.image.img,
			&g->west.image.bpp, &g->west.image.line, &g->west.image.endian);
	g->east.image.pixels = mlx_get_data_addr(g->east.image.img,
			&g->east.image.bpp, &g->east.image.line, &g->east.image.endian);
	if (!g->north.image.pixels || !g->south.image.pixels
		|| !g->west.image.pixels || !g->east.image.pixels)
		exit((perror("mlx_get_data_addr()"), 1));
}

void	init_textures(t_data *data)
{
	t_game	*g;

	g = get_addr_t_game(NULL);
	g->north.filename = data->no;
	g->south.filename = data->so;
	g->west.filename = data->we;
	g->east.filename = data->ea;
	convert_xpm_to_images();
}

void	api(char *filename)
{
	t_data	*data;
	t_game	*game;

	game = get_addr_t_game(NULL);
	data = parse_input(filename);
	if (!data)
	{
		printf("Failed to parse map or map invalid.\n");
		exit(1);
	}
	game->map = data->map;
	game->mapy = data->map_y;
	game->ply.position.x = (data->player_x) * game->tilesz;
	game->ply.position.y = (data->player_y) * game->tilesz;
	if (data->player_d == 'E')
		game->ply.angle = deg2rad(0);
	else if (data->player_d == 'W')
		game->ply.angle = deg2rad(180);
	else if (data->player_d == 'N')
		game->ply.angle = deg2rad(90);
	else if (data->player_d == 'S')
		game->ply.angle = deg2rad(270);
	game->ceiling_color = data->c;
	game->floor_color = data->f;
	init_textures(data);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	init_game(&game);
	api(argv[1]);
	display(&game);
	hooks(&game);
	mlx_loop(game.mlx);
}
