/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:29 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/22 11:30:48 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int mapx = 8, mapy  = 8, maps;

int map[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
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

