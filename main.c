#include "cub3d.h"

int grid[6][6] = {
    {1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1}
};

void    DDA(t_vec p0, t_vec p1, t_game *data)
{
	int		dx;
    int		dy;
	float	Xinc, Yinc;
	float	x, y;
    int		steps;

    printf("Xp0 = %d | Yp0 = %d\nXp1 = %d | Yp1 = %d\n", p0.x, p0.y, p1.x, p1.y);
    //
    dx = p1.x - p0.x;
    dy = p1.y - p0.y;
    printf("Xd = %d | Yd = %d\n", dx, dy);

    // steps 
    steps = dx;
    if (dx < dy)
        steps = dy;
    // calculate increment in x & y for each steps
    Xinc = (float)(dx / (float)steps);
    Yinc = (float)(dy / (float)steps);
    printf("Xinc = %f | Yinc = %f\n", Xinc, Yinc);

    // draw line in the window
    x = p0.x;
	y = p0.y;
    printf("x = %.2f | y = %.2f\n", x, y);
    for (int i = 0; i <= steps; i++)
    {
        // put pixel in this position ...
		mlx_pixel_put(data->mlx, data->win, x, y, 0xFFFFFF);
        x += Xinc;
        y += Yinc;
        printf("x = %.2f | y = %.2f\n", x, y);
    }
}

void    display_grid(t_game *data)
{
    int x, y;

    x = 0;
    y = 0;
    for (int y = 0; y < W; y++)
    {
        for (int x = 0; x < H; x++)
        {
            ;
        }
    }
    
}

int main(int argc, char const *argv[])
{
	t_game data;

    init_data(&data);
    // display_grid(&data);
    mlx_big_point(&data, 4, 0xff00);
    
    mlx_hook(data.win, 17, 0, close_win, NULL);
    mlx_key_hook(data.win, keyboard, &data);;
	mlx_loop(data.mlx);
	// DDA((t_vec){200, 200}, (t_vec){205, 202}, &data);
}
