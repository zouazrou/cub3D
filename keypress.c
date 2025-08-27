/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:39:57 by zouazrou          #+#    #+#             */
/*   Updated: 2025/08/27 13:42:21 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[8][8];

void check_wall(t_game *g, t_vd new_position)
{
    // if (new_position.x < g->tilesz / 10)
    //     new_position.x = g->tilesz / 10;
    // if (new_position.y < g->tilesz / 10)
    //     new_position.y = g->tilesz / 10;
    // if (new_position.x > WIDTH - g->tilesz / 10)
    //     new_position.x = WIDTH - g->tilesz / 10;
    // if (new_position.y > HEIGHT - g->tilesz / 10)
    //     new_position.y = HEIGHT - g->tilesz / 10;
    int index_x;
    int index_y;

    index_x = (int)(new_position.x) / g->tilesz;
    index_y = (int)(new_position.y) / g->tilesz;
    if (map[index_y][index_x] == 0)
        g->ply.position = new_position;
    else
        printf(TXT_YELLOW"ERR : WALL !!\n"RESET);
}
void change_position(int keysym, t_game *g)
{
    double  move;
    t_vd    new_position;
    
    move = g->ply.move_speed;
    new_position = g->ply.position;
    if (keysym == XK_w) // forward
    {
        new_position.x += cos(g->ply.angle) * move;
        new_position.y += sin(g->ply.angle) * move;
    }
    if (keysym == XK_s) // backward
    {
        new_position.x -= cos(g->ply.angle) * move;
        new_position.y -= sin(g->ply.angle) * move;
    }
    if (keysym == XK_a)
    {
        new_position.x += cos(g->ply.angle - PI/2) * move;
        new_position.y += sin(g->ply.angle - PI/2) * move;
    }
    if (keysym == XK_d)
    {
        new_position.x += cos(g->ply.angle + PI/2) * move;
        new_position.y += sin(g->ply.angle + PI/2) * move;
    }
    if (new_position.x < g->tilesz/10)
        new_position.x = g->tilesz/10;
    if (new_position.y < g->tilesz/10)
        new_position.y = g->tilesz/10;
    check_wall(g, new_position);
    // if (!check_wall(g, new_position))
        // g->ply.position = new_position;  
}

void change_angle(int keysym, t_game *g)
{
    if (keysym == XK_Left)
        g->ply.angle = normalize_angle(g->ply.angle - g->ply.rotation_speed);
    if (keysym == XK_Right)
        g->ply.angle = normalize_angle(g->ply.angle + g->ply.rotation_speed);
    // g->ply.direction.x = cos(g->ply.angle);
    // g->ply.direction.y = sin(g->ply.angle);
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
		ft_clean(data, true);
    
    change_position(keysym, data);
    change_angle(keysym, data);
    display(data);
	return (0);   
}