/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utlis_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 03:26:49 by melayyad          #+#    #+#             */
/*   Updated: 2025/09/26 09:46:35 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	after_last_line(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i] && data->map[i][0] == '\n')
		i++;
	while (data->map[i] && data->map[i][0] != '\n')
		i++;
	while (data->map[i] && data->map[i][0] == '\n')
		i++;
	if ((data->map[i]) && (data->map[i][0] != '\0' && data->map[i][0] != '\n'))
		return (1);
	return (0);
}

char	**my_realloc(char **old, int old_size)
{
	char	**new_mem;
	int		i;

	i = 0;
	new_mem = malloc(sizeof(char *) * (old_size + 2));
	if (!new_mem)
		return (NULL);
	while (i < old_size)
	{
		new_mem[i] = old[i];
		i++;
	}
	free(old);
	return (new_mem);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == '\n');
}

void	init_dirs(int dy[4], int dx[4])
{
	dy[0] = -1;
	dy[1] = 1;
	dy[2] = 0;
	dy[3] = 0;
	dx[0] = 0;
	dx[1] = 0;
	dx[2] = -1;
	dx[3] = 1;
}

int	check_neighbors(char **map, int y, int x)
{
	int	dy[4];
	int	dx[4];
	int	i;
	int	ny;
	int	nx;

	init_dirs(dy, dx);
	i = 0;
	while (i < 4)
	{
		ny = y + dy[i];
		nx = x + dx[i];
		if (ny < 0 || nx < 0 || !map[ny] || nx >= (int)ft_strlen(map[ny]))
			return (0);
		if (map[ny][nx] == ' ' || map[ny][nx] == '\n' || map[ny][nx] == '\0')
			return (0);
		i++;
	}
	return (1);
}
