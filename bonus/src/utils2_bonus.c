/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 09:20:46 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/25 09:52:29 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	distance(t_vd p0, t_vd p1)
{
	return (sqrt(pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2)));
}

double	deg2rad(int degree)
{
	return (degree * (PI / 180));
}

double	normalize_angle(double radian)
{
	radian = fmod(radian, (PI * 2));
	if (radian < 0)
		radian += (PI * 2);
	return (radian);
}

double	fix_fish_eye(int index)
{
	t_game	*g;

	g = get_addr_t_game(NULL);
	return (g->ray[index].distance * cos(g->ply.angle - g->ray[index].angle));
}

void	convert_xpm_to_images(t_game *g)
{
	g->north.image.img = mlx_xpm_file_to_image(g->mlx, g->north.filename,
			&g->north.w, &g->north.h);
	g->south.image.img = mlx_xpm_file_to_image(g->mlx, g->south.filename,
			&g->south.w, &g->south.h);
	g->west.image.img = mlx_xpm_file_to_image(g->mlx, g->west.filename,
			&g->west.w, &g->west.h);
	g->east.image.img = mlx_xpm_file_to_image(g->mlx, g->east.filename,
			&g->east.w, &g->east.h);
	if (!g->north.image.img || !g->south.image.img || !g->west.image.img
		|| !g->east.image.img)
	{
		ft_perror(NULL);
		ft_clean(-1, g);
	}
	g->north.image.pixels = mlx_get_data_addr(g->north.image.img,
			&g->north.image.bpp, &g->north.image.line, &g->north.image.endian);
	g->south.image.pixels = mlx_get_data_addr(g->south.image.img,
			&g->south.image.bpp, &g->south.image.line, &g->south.image.endian);
	g->west.image.pixels = mlx_get_data_addr(g->west.image.img,
			&g->west.image.bpp, &g->west.image.line, &g->west.image.endian);
	g->east.image.pixels = mlx_get_data_addr(g->east.image.img,
			&g->east.image.bpp, &g->east.image.line, &g->east.image.endian);
}
