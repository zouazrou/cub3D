/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:39:57 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/19 08:22:34 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void change_position(int keysym, t_game *data)
{
    t_vi    p = data->p;
    int     speed = data->sp;

    if (keysym == XK_w)
    {
        if ((p.y - speed >= speed))
            data->p.y -= speed;
        else
            data->p.y = speed;		
    }
    else if (keysym == XK_s)
    {
        if ((p.y + speed < H))
            data->p.y += speed;
        else
            data->p.y = H-speed;
    }
    else if (keysym == XK_a)
    {
        if ((p.x - speed >= speed))
            data->p.x -= speed;
        else
            data->p.x = speed;		
    }
    else if (keysym == XK_d)
    {
        if ((p.x + speed < W))
            data->p.x += speed;
        else
            data->p.x = W-speed;
    }
}
void change_angle(int keysym, t_game *data)
{
    if (keysym == XK_Left)
    {
        data->pa -= 0.1;
        if (data->pa < 0)
            data->pa += (PI*2);
    }
    if (keysym == XK_Right)
    {
        data->pa += 0.1;
        if (data->pa >= PI*2)
            data->pa -= PI*2;
    }
    data->d.x = cos(data->pa);
    data->d.y = sin(data->pa);
    // printf("cos()=%f\n", cos(data->pa));
    // printf("cos()=%f\n", data->d.x);
    // printf("sin()=%f\n", sin(data->pa));
    // printf("sin()=%f\n", data->d.y);
    // printf("dubeg : change_angle()\ndx = %.1f ; dy = %.1f| angle = %.1f\n", data->p.x, data->p.y,data->pa);
    return;
}
int  close_win(void *ptr)
{
    printf("Exit !\n");
    exit(0);
}


int keyboard(int keysym, t_game *data)
{
    
    if (keysym == XK_Escape)
		exit((printf("Exit ! (esc)\n"), 0));
    change_position(keysym, data);
    change_angle(keysym, data);
    

    display(data);
	return (0);   
}