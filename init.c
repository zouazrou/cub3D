/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:27:15 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/01 11:29:43 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int bpp;
extern int line_bytes;
extern int endian;

void    init_ray(t_game *g)
{
    g->ray = calloc(g->num_rays, sizeof(t_ray));
    if (!g->ray)
        exit((perror("malloc()"), 1));
}

void    init_player(t_game *g)
{
    g->ply.move_speed = 0.1 * g->tilesz;
    g->ply.rotation_speed = deg2rad(3);
    
    // ? Player's Postion
    g->ply.position.x = (1.5) * g->tilesz;
    g->ply.position.y = (1.5) * g->tilesz;
        // ? angle by rad
    g->ply.angle = deg2rad(20);
    // ? convert angle to vector
    // g->ply.direction.x = cos(g->ply.angle);
    // g->ply.direction.y = sin(g->ply.angle);
}

void    init_textures(t_game *g)
{
    // * PATH XMP IMGS
    g->north.filename = "image/eagle.xpm";
    g->south.filename = "image/eagle.xpm";
    g->west.filename = "image/eagle.xpm";
    g->east.filename = "image/eagle.xpm";

    // * CONVERT 'xpm' TO 'IMG' 
    g->north.image.img = mlx_xpm_file_to_image(g->mlx, g->north.filename, &g->north.w, &g->north.h);
    g->south.image.img = mlx_xpm_file_to_image(g->mlx, g->south.filename, &g->south.w, &g->south.h);
    g->west.image.img = mlx_xpm_file_to_image(g->mlx, g->west.filename, &g->west.w, &g->west.h);
    g->east.image.img = mlx_xpm_file_to_image(g->mlx, g->east.filename, &g->east.w, &g->east.h);
    if (!g->north.image.img || !g->south.image.img || !g->west.image.img || !g->east.image.img)
        exit((perror("mlx_xpm_file_to_image()"), 1));

    // 
    g->north.image.pixels = mlx_get_data_addr(g->north.image.img, &g->north.image.bpp, &g->north.image.line, &g->north.image.endian);
    g->south.image.pixels = mlx_get_data_addr(g->south.image.img, &g->south.image.bpp, &g->south.image.line, &g->south.image.endian);
    g->west.image.pixels = mlx_get_data_addr(g->west.image.img, &g->west.image.bpp, &g->west.image.line, &g->west.image.endian);
    g->east.image.pixels = mlx_get_data_addr(g->east.image.img, &g->east.image.bpp, &g->east.image.line, &g->east.image.endian);
    if (!g->north.image.pixels || !g->south.image.pixels || !g->west.image.pixels || !g->east.image.pixels)
        exit((perror("mlx_get_data_addr()"), 1));
}
void    init_data(t_game *g)
{
    // ? screen setting
    g->resolution = 1;
    g->tilesz = 64;
    g->num_rays = WIDTH / g->resolution;
    printf(TXT_GREEN "RAYS NUM -> %d" RESET "\n", g->num_rays);

    
    g->fov = deg2rad(60);
    // ? Player
    init_player(g);
    
    init_ray(g);

    // ? MAP & MLX
    g->mapx = 8;
    g->mapy = 8;
    /***********/
    g->mlx = mlx_init();
    if (!g->mlx)
        exit((perror("mlx_int()"), 1));
    /***********/
    /***********/
    g->win_3d = mlx_new_window(g->mlx, WIDTH, HEIGHT, "3D");
    if (!g->win_3d)
        exit((perror("mlx_new_window()"), 42));
    g->img_3d.img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
    if (!g->img_3d.img)
        exit((perror("mlx_new_image()"), 42));
    g->img_3d.pixels = mlx_get_data_addr(g->img_3d.img, &g->img_3d.bpp, &g->img_3d.line, &g->img_3d.endian);
    if (!g->img_3d.pixels)
        exit((perror("mlx_get_data_addr()"), 42));
    // ! TEXTURES
    init_textures(g);
    
    // ? Plane
        // * <=> DIS-TO-PLANE = WIDTH / TAN(FOV/2)
    g->distance_to_plane = (WIDTH/2.0) / (tan(g->fov/2.0)); // 
    // g->distance_to_plane *= 0.66;
    printf(TXT_CYAN"distance to plane [%.2f]\n"RESET, g->distance_to_plane);
    g->ceiling_color = LIGHT_BLUE;
    g->floor_color = DARK_GRAY;
    // ? ray
    // printf("debug: angle [%f]>>dx[%f]>>dy[%f]\n\n", g->pa, g->d.x, g->d.y);
}


void    draw_big_point(t_img *img, int x, int y,  int r, int col)
{
    for (int dx = -r; dx <= r; dx++)
    {
        for (int dy = -r; dy <= r; dy++)
        {
            if (dx*dx + dy*dy <= r*r) // inside circle
                put_pixel_in_image(img, x + dx, y + dy, col);
        }
    }
}
/*
? Wall-Height / dis-to-the-Wall
!            == 
? Projected-Wall-Height / dis-ply-to-projection-plane  


*/