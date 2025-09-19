/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 08:22:29 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/19 11:36:40 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ms	get_time(void)
{
	struct timeval	time;

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
        printf(TXT_CYAN"\n====================================================\n"RESET);
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

void    api(t_game *game, char *filename)
{
	t_data  *data;
    
    data = parse_input(filename);
	if (!data)
	{
		printf("Failed to parse map or map invalid.\n");
		exit(1);
	}
    game->map = data->map;
    /******/
    
    /******/
    game->mapy = 100;
    game->ply.position.x = (data->player_x + 0.5) * game->tilesz;
    game->ply.position.y = (data->player_y + 0.5) * game->tilesz;
    printf("ply [%.2f : %.2f]\n", game->ply.position.x, game->ply.position.y);
    // game->ceiling_color = data->C;
    // game->floor_color = data->F;
}
bool init_game_map(t_game *g);

int main(int argc, char *argv[])
{
	t_game  game;

    if (argc != 2)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
    init_game(&game);
    
    printf(TXT_YELLOW"WIDTH = %d | g->height = %d\n"RESET, game.width, game.height);
    init_game_map(&game);
    // api(&game, argv[1]);
    

    display(&game);
    hooks(&game);
	mlx_loop(game.mlx);
}

char **init_map(void)
{
    char **map;
    int i;
    char *map_data[] = {
    "1111111     111111", // ! 0
    "10000001   100001", // ! 1
    "100000001 100001", // ! 2
    "100000000100100011", // ! 3
    "1111111100000000001111111", // ! 4
    "        100000000000000001", // ! 5
    "       100000000000000001", // ! 6
    "      100000001111000001", // ! 7
    "     1000000001  100001", // ! 8
    "    100000000011110001", // ! 9
    "   100000000000000001", // ! 10
    "  100000000000000001", // ! 11
    " 100000000000000001", // ! 12
    "111111111111111111", // ! 13
    NULL
    };

    // Count rows to allocate proper array size
    i = 0;
    while (map_data[i])
        i++;
    
    // Allocate array of string pointers (+1 for NULL terminator)
    map = (char **)malloc(sizeof(char *) * (i + 1));
    if (!map)
        return (NULL);
    
    // Copy each row with proper memory allocation
    i = 0;
    while (map_data[i])
    {
        map[i] = ft_strdup(map_data[i]);
        if (!map[i])
        {
            // Free previously allocated memory on error
            while (--i >= 0)
                free(map[i]);
            free(map);
            return (NULL);
        }
        i++;
    }
    map[i] = NULL; // NULL terminate the array
    
    return (map);
}

bool init_game_map(t_game *g)
{
    g->map = init_map();
    if (!g->map)
        return (false);
    
    // Set map dimensions for ray calculations
    g->mapy = 14; // Number of rows
    
    return (true);
}