/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:30:35 by melayyad          #+#    #+#             */
/*   Updated: 2025/09/25 10:06:42 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	if (data->map)
		free_str_array(data->map);
	get_next_line(-1);
	free(data);
}

void	data_init(t_data *data)
{
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->c = -1;
	data->f = -1;
	data->player_d = -1;
	data->player_x = -1;
	data->player_y = -1;
	data->map_y = -1;
	data->map = NULL;
}
