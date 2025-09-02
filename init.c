/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:27:15 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/02 23:36:34 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_ray(t_game *g)
{
    g->ray = calloc(g->num_rays, sizeof(t_ray));
    if (!g->ray)
        exit((perror("malloc()"), 1));
}

void    init_screen(t_game *g)
{
    g->resolution = 1;
    g->tilesz = 64;
    g->num_rays = g->width / g->resolution;
    g->fov = deg2rad(60);
    g->distance_to_plane = (g->width/2.0) / (tan(g->fov/2.0)); // 
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
    g->ply.position.x = (1.5) * g->tilesz;
    g->ply.position.y = (1.5) * g->tilesz;
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
void    init_textures(t_game *g)
{
    // * PATH XMP IMGS
    g->north.filename = "image/eagle.xpm";
    g->south.filename = "image/blue_wall.xpm";
    g->west.filename = "image/grey_wall.xpm";
    g->east.filename = "image/orange_wall.xpm";

    // * CONVERT 'xpm' TO 'IMG' 
    g->north.image.img = mlx_xpm_file_to_image(g->mlx, g->north.filename, &g->north.w, &g->north.h);
    g->south.image.img = mlx_xpm_file_to_image(g->mlx, g->south.filename, &g->south.w, &g->south.h);
    g->west.image.img = mlx_xpm_file_to_image(g->mlx, g->west.filename, &g->west.w, &g->west.h);
    g->east.image.img = mlx_xpm_file_to_image(g->mlx, g->east.filename, &g->east.w, &g->east.h);
    if (!g->north.image.img || !g->south.image.img || !g->west.image.img || !g->east.image.img)
        exit((perror("mlx_xpm_file_to_image()"), 1));
    // * CONVERT TEXTURE TO buffer 'char *'
    g->north.image.pixels = mlx_get_data_addr(g->north.image.img, &g->north.image.bpp, &g->north.image.line, &g->north.image.endian);
    g->south.image.pixels = mlx_get_data_addr(g->south.image.img, &g->south.image.bpp, &g->south.image.line, &g->south.image.endian);
    g->west.image.pixels = mlx_get_data_addr(g->west.image.img, &g->west.image.bpp, &g->west.image.line, &g->west.image.endian);
    g->east.image.pixels = mlx_get_data_addr(g->east.image.img, &g->east.image.bpp, &g->east.image.line, &g->east.image.endian);
    if (!g->north.image.pixels || !g->south.image.pixels || !g->west.image.pixels || !g->east.image.pixels)
        exit((perror("mlx_get_data_addr()"), 1));
}
void    init_data(t_game *g)
{
    ft_bzero(g, sizeof(t_game));
    
    g->mapx = 16;
    g->mapy = 16;
    g->width = WIDTH;
    g->height = HEIGHT;
    g->ceiling_color = LIGHT_BLUE;
    g->floor_color = DARK_GRAY;
    
    init_screen(g);
    init_player(g);
    init_ray(g);
    init_minilibx(g);
    init_textures(g);
    
}

/*
? Wall-Height / dis-to-the-Wall
!            == 
? Projected-Wall-Height / dis-ply-to-projection-plane  


*/