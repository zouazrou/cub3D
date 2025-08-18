#include "cub3d.h"

void    DDA(t_vi end_point, t_game *data)
{
	int		dx;
    int		dy;
	float	Xinc, Yinc;
	float	x, y;
    int		steps;
    // DDA((t_vi){data->ppos.x+data->pdir.x*5, data->ppos.y+data->pdir.y*5}, data);


    // printf("Xp0 = %d | Yp0 = %d\nXend_point = %d | Yend_point = %d\n", p0.x, p0.y, end_point.x, end_point.y);
    //
    dx = end_point.x - data->ppos.x;
    dy = end_point.y - data->ppos.y;
    // printf("Xd = %d | Yd = %d\n", dx, dy);

    // steps 
    steps = dx;
    if (dx < dy)
        steps = dy;
    // calculate increment in x & y for each steps
    Xinc = (float)(dx / (float)steps);
    Yinc = (float)(dy / (float)steps);
    // printf("Xinc = %f | Yinc = %f\n", Xinc, Yinc);

    // draw line in the window
    x = data->ppos.x;
	y = data->ppos.y;
    // printf("x = %.2f | y = %.2f\n", x, y);
    for (int i = 0; i <= steps; i++)
    {
        // put pixel in this position ...
		// !mlx_pixel_put(data->mlx, data->win, x, y, 0xFFFFFF);
        // put_pixel_in_image(data->image,, 0x0);
        draw_big_point(data->image, (t_vi){x, y}, 3, GREEN);
        x += Xinc;
        y += Yinc;
        // printf("x = %.2f | y = %.2f\n", x, y);
    }
}