/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 10:55:28 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/21 13:40:24 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_texture	*select_texture(t_game *g, t_ray *ray)
{
	if (ray->side == WEST)
		return (&g->west);
	if (ray->side == NORTH)
		return (&g->north);
	if (ray->side == SOUTH)
		return (&g->south);
	if (ray->side == EAST)
		return (&g->east);
	return (NULL);
}

unsigned int	get_pixel_color(t_texture *texture, int x, int y)
{
	int	offset;

	if (x < 0 || x >= texture->w || y < 0 || y >= texture->h)
	{
		printf(TXT_BLUE "get_pxl_color()\n" RESET);
		return (0);
	}
	offset = (y * texture->image.line) + (x * (texture->image.bpp / 8));
	return ((*(unsigned int *)(texture->image.pixels + offset)) & 0x00FFFFFF);
}

int	calculate_tex_x(t_game *g, t_ray *ray, t_texture *texture)
{
	int		tex_x;
	double	wall_x;

	if (ray->axis == HORIZONTAL)
		wall_x = ray->inter.x;
	else
		wall_x = ray->inter.y;
	wall_x -= floor(wall_x / g->tilesz) * g->tilesz;
	tex_x = (int)(wall_x / g->tilesz * texture->w);
	if ((ray->axis == VERTICAL && cos(ray->angle) < 0)
		|| (ray->axis == HORIZONTAL && sin(ray->angle) > 0))
		tex_x = texture->w - tex_x - 1;
	return (tex_x);
}

void	draw_cube(int idx, int begin_y, int end_y, int wall_height)
{
	t_game		*g;
	t_data_tex	tex;
	int			begin_x;

	g = get_addr_t_game(NULL);
	begin_x = idx * g->resolution;
	tex.texture = select_texture(g, g->ray + idx);
	tex.tex_x = calculate_tex_x(g, g->ray + idx, tex.texture);
	tex.tex_step = (double)tex.texture->h / wall_height;
	tex.tex_pos = (begin_y - g->height / 2.0 + wall_height / 2.0)
		* tex.tex_step;
	tex.y = begin_y - 1;
	while (++tex.y < end_y)
	{
		tex.tex_y = (int)tex.tex_pos & (tex.texture->h - 1);
		tex.tex_pos += tex.tex_step;
		tex.color = get_pixel_color(tex.texture, tex.tex_x, tex.tex_y);
		tex.x = -1;
		while (++tex.x < g->resolution)
			put_pixel_in_image(begin_x + tex.x, tex.y, tex.color);
	}
}
