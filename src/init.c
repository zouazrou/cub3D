/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:27:15 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/20 15:33:00 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    init_ray(t_game *g)
{
    g->ray = ft_calloc(g->num_rays, sizeof(t_ray));
    if (!g->ray)
        exit((perror("malloc()"), 1));
}

void    init_screen(t_game *g)
{
    g->resolution = 1;
    g->tilesz = 1;
    g->num_rays = g->width / g->resolution;
    g->fov = deg2rad(60);
    g->distance_to_plane = (g->width/2.0) / (tan(g->fov/2.0));
    printf(TXT_GREEN "RAYS NUM -> %d" RESET "\n", g->num_rays);
}

/*
    ! 0    'W'
    ! 180  'E'
    ! 90   'S'
    ! 270  'N'
*/
void    init_player(t_game *g)
{
    g->ply.move_speed = 0.1 * g->tilesz;
    g->ply.rotation_speed = deg2rad(3);
    g->ply.position.x = (20) * g->tilesz;
    g->ply.position.y = (7.5) * g->tilesz;
    g->ply.angle = deg2rad(270);
}
void    init_minilibx(t_game *g)
{
    g->mlx = mlx_init();
    if (!g->mlx)
        exit((perror("mlx_int()"), 1));
    g->win_3d = mlx_new_window(g->mlx, g->width, g->height, "3D");
    if (!g->win_3d)
        exit((perror("mlx_new_window()"), 42));
    g->img_3d.img = mlx_new_image(g->mlx, g->width, g->height);
    if (!g->img_3d.img)
        exit((perror("mlx_new_image()"), 42));
    g->img_3d.pixels = mlx_get_data_addr(g->img_3d.img, &g->img_3d.bpp, &g->img_3d.line, &g->img_3d.endian);
    if (!g->img_3d.pixels)
        exit((perror("mlx_get_data_addr()"), 42));
}

void    init_game(t_game *g)
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
    // init_textures(g);
    
}

/*
? Wall-Height / dis-to-the-Wall
!            == 
? Projected-Wall-Height / dis-ply-to-projection-plane  


*/