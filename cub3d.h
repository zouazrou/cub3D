#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>


#define CELLSIZE 16
#define W 500
#define H 500
/*

*/

typedef struct s_vec
{
    double     x;
    double     y;
} t_vec;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    /*position Player*/
    t_vec  pos;
    /*direction Player*/
    t_vec  dir;
    /*Fov Player*/
    t_vec  plane;
    /*FPS*/
    double  time;
    double  oldtime;
    // x-coordinate h
}   t_game;

void    mlx_big_point(t_game *data, int r, int color);
int close_win(void *ptr);

int			keyboard(int keysym, t_game *map);
void    init_data(t_game *data);

#endif