/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:39:57 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/23 20:42:09 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void change_position(int keysym, t_game *g)
{
    t_vi    p = g->p;
    int     speed = g->move_speed;

    if (keysym == XK_w)
    {
        if ((p.y - speed >= speed))
            g->p.y -= speed;
        else
            g->p.y = speed;		
    }
    else if (keysym == XK_s)
    {
        if ((p.y + speed < HEIGHT))
            g->p.y += speed;
        else
            g->p.y = HEIGHT-speed;
    }
    else if (keysym == XK_a)
    {
        if ((p.x - speed >= speed))
            g->p.x -= speed;
        else
            g->p.x = speed;		
    }
    else if (keysym == XK_d)
    {
        if ((p.x + speed < WIDTH))
            g->p.x += speed;
        else
            g->p.x = WIDTH-speed;
    }
}
void change_angle(int keysym, t_game *g)
{
    if (keysym == XK_Left)
        g->pa = normalize_angle(g->pa - g->rotation_speed);
    if (keysym == XK_Right)
        g->pa = normalize_angle(g->pa + g->rotation_speed);
    g->d.x = cos(g->pa);
    g->d.y = sin(g->pa);
    return;
}
int  close_win(void *ptr)
{
    (void)ptr;
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