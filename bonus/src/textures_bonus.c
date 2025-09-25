/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:39:45 by melayyad          #+#    #+#             */
/*   Updated: 2025/09/25 10:06:42 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	trim_end(char *s)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == ' ' || s[len
				- 1] == '\t'))
		len--;
	s[len] = '\0';
}

static void	assign_texture(char **dst, char *path, int *flag)
{
	int	i;

	if (*dst)
	{
		*flag = 1;
		return ;
	}
	path = skip_ws(path);
	i = ft_strlen(skip_ws(path));
	trim_end(path);
	*dst = ft_strdup(skip_ws(path));
	if (!*dst)
		*flag = 2;
}

void	if_process(t_data *data, char *tmp, int *flag)
{
	if (!ft_strncmp(skip_ws(tmp), "NO", 2))
		assign_texture(&data->no, tmp + 2, flag);
	else if (!ft_strncmp(skip_ws(tmp), "SO", 2))
		assign_texture(&data->so, tmp + 2, flag);
	else if (!ft_strncmp(skip_ws(tmp), "WE", 2))
		assign_texture(&data->we, tmp + 2, flag);
	else if (!ft_strncmp(skip_ws(tmp), "EA", 2))
		assign_texture(&data->ea, tmp + 2, flag);
	else if (is_color_line(skip_ws(tmp)))
		parse_color(tmp, data);
}
