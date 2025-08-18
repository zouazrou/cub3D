#include "cub3d.h"

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