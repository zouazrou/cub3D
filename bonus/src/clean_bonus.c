/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:32:19 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/24 18:52:18 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_perror(char *str)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (str)
		ft_putendl_fd(str, STDERR_FILENO);
	else
		perror(NULL);
}

void	destroy_images(t_game *g)
{
	if (g->north.image.img)
		mlx_destroy_image(g->mlx, g->north.image.img);
	if (g->south.image.img)
		mlx_destroy_image(g->mlx, g->south.image.img);
	if (g->west.image.img)
		mlx_destroy_image(g->mlx, g->west.image.img);
	if (g->east.image.img)
		mlx_destroy_image(g->mlx, g->east.image.img);
	g->north.image.img = NULL;
	g->south.image.img = NULL;
	g->west.image.img = NULL;
	g->east.image.img = NULL;
}

int	destroy_notify_func(t_game *game)
{
	ft_clean(XK_Escape, game);
	return (0);
}

int	ft_clean(int keysym, t_game *g)
{
	g = get_addr_t_game(NULL);
	free_data(get_addr_t_data(NULL));
	free(g->ray);
	destroy_images(g);
	g->map = NULL;
	if (g->win_3d)
		mlx_destroy_window(g->mlx, g->win_3d);
	if (g->img.img)
		mlx_destroy_image(g->mlx, g->img.img);
	if (g->mlx)
		mlx_destroy_display(g->mlx);
	free(g->mlx);
	g->win_3d = NULL;
	g->img.img = NULL;
	g->mlx = NULL;
	if (keysym == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
