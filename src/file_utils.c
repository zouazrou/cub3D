/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:32:18 by melayyad          #+#    #+#             */
/*   Updated: 2025/09/20 12:10:27 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_dot_cub(const char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	return (len > 4 && !ft_strncmp(filename + len - 4, ".cub", 4));
}

t_data	*init_data(char *input, int *fd)
{
	t_data	*data;

	if (!is_dot_cub(input))
		return (print_error("Error: File must have .cub extension\n", 0), NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		return (print_error("Malloc: ", 1), NULL);
	data_init(data);
	*fd = open(input, O_RDONLY);
	if (*fd < 0)
		return (free_data(data), print_error("Open: ", 1), NULL);
	return (data);
}
