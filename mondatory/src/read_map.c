/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 03:21:23 by melayyad          #+#    #+#             */
/*   Updated: 2025/09/24 18:27:59 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	handle_first_empty_line(char *line, int count)
{
	char	*x;

	x = skip_ws(line);
	if ((ft_strlen(x) == 1 && x[0] == '\n') && (count == 0))
	{
		free(line);
		return (1);
	}
	return (0);
}

static int	init_map(t_data *data, char *line, int *count)
{
	data->map = malloc(sizeof(char *) * 2);
	if (!data->map)
		return (1);
	data->map[0] = line;
	data->map[1] = NULL;
	*count = 1;
	return (0);
}

static int	append_line(t_data *data, char *line, int *count)
{
	data->map = my_realloc(data->map, *count);
	if (!data->map)
		return (free(line), 1);
	data->map[*count] = line;
	(*count)++;
	data->map[*count] = NULL;
	return (0);
}

int	read_map(int fd, t_data *data)
{
	int		count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (handle_first_empty_line(line, count))
		{
			line = get_next_line(fd);
			continue ;
		}
		if ((!data->map && line) && (line[0] != '\0' && line[0] != '\n'))
		{
			if (init_map(data, line, &count))
				return (1);
			line = get_next_line(fd);
			continue ;
		}
		if (append_line(data, line, &count))
			return (1);
		line = get_next_line(fd);
	}
	return (0);
}
