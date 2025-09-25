/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:29:46 by melayyad          #+#    #+#             */
/*   Updated: 2025/09/24 18:52:24 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_color_line(char *s)
{
	s = skip_ws(s);
	return (*s == 'F' || *s == 'C');
}

int	validate_rgb_part(char *part, int *value)
{
	char	*trimmed;

	if (!part)
		return (0);
	trimmed = ft_strtrim(part, "\n\r\t ");
	if (!trimmed)
		return (0);
	if (!is_all_digits(trimmed))
		return (free(trimmed), 0);
	*value = ft_atoi(trimmed);
	if (*value < 0 || *value > 255)
		return (free(trimmed), 0);
	free(trimmed);
	return (1);
}

void	parse_color(char *color, t_data *data)
{
	char	**str;
	int		rgb[3];

	color = skip_ws(color);
	if (color[0] != 'F' && color[0] != 'C')
		return ;
	str = ft_split(color + 1, ',');
	if (!str)
		return ;
	if (!validate_rgb_part(str[0], &rgb[0]) || !validate_rgb_part(str[1],
			&rgb[1]) || !validate_rgb_part(str[2], &rgb[2]) || str[3])
	{
		free_str_array(str);
		return ;
	}
	if (color[0] == 'F' && data->f < 0)
		data->f = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	else if (color[0] == 'C' && data->c < 0)
		data->c = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	free_str_array(str);
}
