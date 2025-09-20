/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:29 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/20 15:19:09 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_ms get_time(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((t_ms)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

int frames(t_game *data)
{
    static t_ms last_frame;
    static int diff = 1000 / FPS;

    if (get_time() - last_frame >= diff)
    {
        last_frame = get_time();
        display(data);
        printf(TXT_CYAN "\n====================================================\n" RESET);
    }
    return (0);
}
void hooks(t_game *data)
{
    /******/
    mlx_hook(data->win_3d, DestroyNotify, 0, ft_clean, NULL);
    /******/
    mlx_hook(data->win_3d, KeyPress, KeyPressMask, keyboard, data);
    mlx_loop_hook(data->mlx, frames, data);
}

void    init_textures(t_data *data)
{
    t_game *g;

    g = get_addr_t_game(NULL);
    // * PATH XMP IMGS
    g->north.filename = data->no;
    g->south.filename = data->so;
    g->west.filename = data->we;
    g->east.filename = data->ea;

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

void api(char *filename)
{
    t_data *data;
    t_game *game;

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
    printf("ply [%.2f : %.2f]\n", game->ply.position.x, game->ply.position.y);
    game->ceiling_color = data->c;
    game->floor_color = data->f;
    init_textures(data);
    
}

int main(int argc, char *argv[])
{
    t_game game;

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

// char **init_map(void)
// {
//     char **map;
//     int i;
//     char *map_data[] = {
//         "1111111     111111",                     // ! 0
//         "10000001   100001",                      // ! 1
//         "100000001 100001",                       // ! 2
//         "100000000100100011",                     // ! 3
//         "1111111100000000001111111",              // ! 4
//         "        100000000000000001",             // ! 5
//         "       100000000000000001",              // ! 6
//         "      100000000000000001         ",      // ! 7
//         "     100000000000000001         ",       // ! 8
//         "    100000000000000001         ",        // ! 9
//         "   100000000000000001                 ", // ! 10
//         "  100000000000000001         ",          // ! 11
//         " 100000000000000001",                    // ! 12
//         "111111111111111111",                     // ! 13
//         NULL};

//     // Count rows to allocate proper array size
//     i = 0;
//     while (map_data[i])
//         i++;

//     // Allocate array of string pointers (+1 for NULL terminator)
//     map = (char **)malloc(sizeof(char *) * (i + 1));
//     if (!map)
//         return (NULL);

//     // Copy each row with proper memory allocation
//     i = 0;
//     while (map_data[i])
//     {
//         map[i] = ft_strdup(map_data[i]);
//         if (!map[i])
//         {
//             // Free previously allocated memory on error
//             while (--i >= 0)
//                 free(map[i]);
//             free(map);
//             return (NULL);
//         }
//         i++;
//     }
//     map[i] = NULL; // NULL terminate the array

//     return (map);
// }

// bool init_game_map(t_game *g)
// {
//     g->map = init_map();
//     if (!g->map)
//         return (false);

//     // Set map dimensions for ray calculations
//     g->mapy = 14; // Number of rows

//     return (true);
// }