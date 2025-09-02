/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:55:10 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/02 21:57:46 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool    facing_down(double angle)
{
    if (angle > 0 && angle < PI)
        return (true);
    return (false);
}

bool    facing_up(double angle)
{
    // if (angle > PI && angle < 2 * PI)
    //     return (true);
    // return (false);
    return (!facing_down(angle));
}

bool    facing_right(double angle)
{
    if (angle < PI / 2 || angle > PI * 3 / 2)
        return (true);
    return (false);
}

bool    facing_left(double angle)
{
    // if (angle > PI / 2 && angle < PI * 3 / 2)
    //     return (true);
    // return (false);
    return (!facing_right(angle)); 
}
