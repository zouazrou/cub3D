/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:39:57 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/18 15:02:17 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void change_position(int keysym, t_game *data)
{
    t_vi    p = data->ppos;
    int     speed = data->sp;

    if (keysym == XK_w)
    {
        if ((p.y - speed >= speed))
            data->ppos.y -= speed;
        else
            data->ppos.y = speed;		
    }
    else if (keysym == XK_s)
    {
        if ((p.y + speed < H))
            data->ppos.y += speed;
        else
            data->ppos.y = H-speed;
    }
    else if (keysym == XK_a)
    {
        if ((p.x - speed >= speed))
            data->ppos.x -= speed;
        else
            data->ppos.x = speed;		
    }
    else if (keysym == XK_d)
    {
        if ((p.x + speed < W))
            data->ppos.x += speed;
        else
            data->ppos.x = W-speed;
    }
}
void change_angle(int keysym, t_game *data)
{
    if (keysym == XK_Left)
    {
        data->pa -= 0.1;
        if (data->pa < 0)
            data->pa += (PI*2);
        data->pdir.x = cos(data->pa)*5;
        data->pdir.y = sin(data->pa)*5;
    }
    else if (XK_Right)
    {
        data->pa += 0.1;
        if (data->pa < 2*PI)
            data->pa -= PI*2;
        data->pdir.x = cos(data->pa);
        data->pdir.y = sin(data->pa);
    }
    // printf("dubeg : x = %.1f ; y = %.1f| b dis\n", data->ppos.x, data->ppos.y);
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