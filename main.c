/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:29 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/19 08:58:35 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int mapx = 8, mapy  = 8, maps;

int map[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
};

int bpp;
int tilex, tiley;
int line_bytes;
int endian;

void drow_quade(t_game *data, int x0, int y0, int col)
{
    int TILE_SIZE = W / mapx;
    int start_x = x0 * TILE_SIZE;
    int start_y = y0 * TILE_SIZE;
    char *data_img = mlx_get_data_addr(data->image, &bpp, &line_bytes, &endian);

    // printf("x0 = %d ; y0 %d\n", x0, y0);
    for (int y = 1; y < TILE_SIZE-1; y++)
    {
        for (int x = 1; x < TILE_SIZE-1; x++)
        {
            put_pixel_in_image(data->image, x0 + x, y0 + y, col);
        }
    }
}

void    draw_map2D(t_game *data)
{
    for (int y = 0; y < mapy; y++)
    {
        for (int x = 0; x < mapx; x++)
        {
            if (map[y][x] == 1)
                drow_quade(data, x * tilex, y * tiley, BLACK);
            // else if (map[y][x] == 0)
            //     drow_quade(data, x * tilex, y * tiley, CHI LON);
        }
    }

}
void fill_img(void *img, int col)
{
    // printf("debug : fill_img()\n");
    // printf("bpp = %d| line_bytes = %d| endian=  %d\n", bpp, line_bytes, endian);
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
            put_pixel_in_image(img, x, y, col);
    }
}
void    display(t_game *g)
{
    // !init g_vars
    maps = mapx * mapy;
    tilex = W / mapx;
    tiley = H / mapy;

    // ! Draw
    // printf("debug : draw_map2D()\n");
    fill_img(g->image, BLCK_SHDW);
    draw_map2D(g);
    draw_big_point(g->image, g->p, 4, GREEN);
    // draw direction vector 
    DDA(g->p, (t_vi){g->p.x+g->d.x*17, g->p.y+g->d.y*17}, g, GREEN);
    draw_ray(g);
    // !put image to win
    mlx_put_image_to_window(g->mlx, g->win, g->image, 0, 0);
}


int main(int argc, char const *argv[])
{
	t_game data;

    printf("W = %d | H = %d\n\n", W, H);
    init_data(&data);
    // display_grid(&data);

    display(&data);
    mlx_hook(data.win, DestroyNotify, 0, close_win, NULL);
    mlx_hook(data.win, KeyPress, KeyPressMask, keyboard, &data);
	mlx_loop(data.mlx);
}

