#include "cub3d.h"

void    DDA(t_vi a, t_vi b, t_game *data)
{
	int		dx;
    int		dy;
	double	Xinc, Yinc;
	double	x, y;
    int		steps;


    // printf("Xp0 = %d | Yp0 = %d\nXb = %d | Yb = %d\n", p0.x, p0.y, b.x, b.y);
    //
    dx = b.x - a.x;
    dy = b.y - a.y;
    // printf("Xd = %d | Yd = %d\n", dx, dy);

    // steps 
    steps = abs(dx);
    if (abs(dx) < abs(dy))
        steps = abs(dy);
    // calculate increment in x & y for each steps
    Xinc = (double)(dx / (double)steps);
    Yinc = (double)(dy / (double)steps);
    // printf("Xinc = %f | Yinc = %f\n", Xinc, Yinc);

    // draw line in the window
    x = a.x;
	y = a.y;
    // printf("x = %.2f | y = %.2f\n", x, y);
    int flg = 0;
    for (int i = 0; i <= steps; i++)
    {
        // put pixel in this position ...
		// !mlx_pixel_put(data->mlx, data->win, x, y, 0xFFFFFF);
        draw_big_point(data->image, (t_vi){x, y}, 2, GREEN);
        x += Xinc;
        y += Yinc;
        if (flg == 0)
        {
            printf("x = %f | y = %f\n", x, y);
            flg++;
        }
    }
}