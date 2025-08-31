/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:27:15 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/31 21:34:18 by zouazrou         ###   ########.fr       */
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
        exit((printf("calloc \n"), 1));
}

void    init_player(t_game *g)
{
    g->ply.move_speed = 0.1 * g->tilesz;
    g->ply.rotation_speed = deg2rad(3);
    
    // ? Player's Postion
    g->ply.position.x = (1) * g->tilesz;
    g->ply.position.y = (1) * g->tilesz;
        // ? angle by rad
    g->ply.angle = deg2rad(20);
    // ? convert angle to vector
    // g->ply.direction.x = cos(g->ply.angle);
    // g->ply.direction.y = sin(g->ply.angle);
}

void    init_textures(t_game *g)
{
    // * PATH XMP IMGS
    g->north.file_name = "image/eagle.xpm";
    g->south.file_name = "image/eagle.xpm";
    g->west.file_name = "image/eagle.xpm";
    g->east.file_name = "image/eagle.xpm";

    // * CONVERT 'xpm' TO 'IMG' 
    g->north.img = mlx_xpm_file_to_image(g->mlx, g->north.file_name, &g->north.w, &g->north.h);
    g->south.img = mlx_xpm_file_to_image(g->mlx, g->south.file_name, &g->south.w, &g->south.h);
    g->west.img = mlx_xpm_file_to_image(g->mlx, g->west.file_name, &g->west.w, &g->west.h);
    g->east.img = mlx_xpm_file_to_image(g->mlx, g->east.file_name, &g->east.w, &g->east.h);
    if (!g->north.img || !g->south.img || !g->west.img || !g->east.img)
        exit((printf(TXT_RED"img\n"RESET), 1));

    // 
    g->north.pixels = mlx_get_data_addr(g->north.img, &g->north.bpp, &g->north.line, &g->north.endian);
    g->south.pixels = mlx_get_data_addr(g->south.img, &g->south.bpp, &g->south.line, &g->south.endian);
    g->west.pixels = mlx_get_data_addr(g->west.img, &g->west.bpp, &g->west.line, &g->west.endian);
    g->east.pixels = mlx_get_data_addr(g->east.img, &g->east.bpp, &g->east.line, &g->east.endian);
    if (!g->north.pixels || !g->south.pixels || !g->west.pixels || !g->east.pixels)
        exit((printf(TXT_RED"pixels\n"RESET), 1));
}
void    init_data(t_game *g)
{
    // ? screen setting
    g->resolution = 1;
    g->tilesz = 1;
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
        exit((printf(TXT_RED"-------------------mlx_init \n"RESET), 1));
    /***********/
    /***********/
    g->win_3d = mlx_new_window(g->mlx, WIDTH, HEIGHT, "3D");
    if (!g->win_3d)
        exit((printf(TXT_RED"-------------------mlx_new_win 3D \n"RESET), 42));
    g->img_3d = mlx_new_image(g->mlx, WIDTH, HEIGHT);
    if (!g->img_3d)
        exit((printf(TXT_RED"-------------------mlx_new_img 3D\n"RESET), 42));
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


void    draw_big_point(void *img, int x, int y,  int r, int col)
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