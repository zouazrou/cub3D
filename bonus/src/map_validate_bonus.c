/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:59:24 by melayyad          #+#    #+#             */
/*   Updated: 2025/09/24 18:53:08 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	cases_check(t_data *data, int y, int x, int *player_found)
{
	char	c;

	c = data->map[y][x];
	if (!is_valid_char(c))
		return (ft_perror("Invalid char in map"), 0);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		if (!check_neighbors(data->map, y, x))
			return (ft_perror("Map not closed"), 0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if ((*player_found))
			return (ft_perror("More than one player"), 0);
		data->player_x = x;
		data->player_y = y;
		data->player_d = c;
		*player_found = 1;
	}
	return (1);
}

int	validate_map(t_data *data)
{
	int	y;
	int	x;
	int	player_found;

	y = 0;
	player_found = 0;
	if (!data->map || !data->map[0])
		return (ft_perror("Empty map"), 0);
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (!cases_check(data, y, x, &player_found))
				return (0);
			x++;
		}
		y++;
	}
	data->map_y = y;
	if (!player_found)
		return (ft_perror("No player in map"), 0);
	if (after_last_line(data))
		return (0);
	return (1);
}
