/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:29 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/29 00:29:44 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int map[8][8] = {
//     {1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 1, 1},
//     {1, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1},
// };
int map[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
};

int bpp;
int line_bytes;
int endian;


int handling_mouse_event(int x, int y, void *g)
{
    static int last_pos;
    printf(TXT_RED"mouse [%d, %d]\n"RESET, x, y);

    if (x < last_pos)
        change_angle(XK_Left, g);
    if (x > last_pos)
        change_angle(XK_Right, g);
    last_pos = x;
    display(g);
    return (0);
}

int main(int argc, char const *argv[])
{
	t_game data;

    (void)argc;
    (void)argv;
    printf(TXT_YELLOW"WIDTH = %d | HEIGHT = %d\n"RESET, WIDTH, HEIGHT);
    init_data(&data);

    display(&data);
    /******/
    // mlx_hook(data.win_2d, DestroyNotify, 0, ft_clean, NULL);
    // mlx_hook(data.win_3d, DestroyNotify, 0, ft_clean, NULL);
    /******/
    
    
    mlx_hook(data.win_3d, MotionNotify, PointerMotionMask, handling_mouse_event, &data);
    /*******/
    mlx_hook(data.win_2d, KeyPress, KeyPressMask, keyboard, &data);
    mlx_hook(data.win_3d, KeyPress, KeyPressMask, keyboard, &data);
    // mlx_loop_hook(data.mlx)
	mlx_loop(data.mlx);
}

