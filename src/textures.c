/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:39:45 by melayyad          #+#    #+#             */
/*   Updated: 2025/09/20 12:10:27 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	assign_texture(char **dst, char *path, int *flag)
{
	int	i;

	if (*dst)
	{
		*flag = 1;
		return ;
	}
	i = ft_strlen(skip_ws(path));
	if (path[i] == '\n')
		path[i] = '\0';
	*dst = ft_strdup(skip_ws(path));
	if (!*dst)
		*flag = 2;
}

void	if_process(t_data *data, char *tmp, int *flag)
{
	if (!ft_strncmp(tmp, "NO", 2))
		assign_texture(&data->NO, tmp + 2, flag);
	else if (!ft_strncmp(tmp, "SO", 2))
		assign_texture(&data->SO, tmp + 2, flag);
	else if (!ft_strncmp(tmp, "WE", 2))
		assign_texture(&data->WE, tmp + 2, flag);
	else if (!ft_strncmp(tmp, "EA", 2))
		assign_texture(&data->EA, tmp + 2, flag);
	else if (is_color_line(tmp))
		parse_color(tmp, data);
}
