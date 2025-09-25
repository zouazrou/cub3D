/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 03:46:40 by melayyad          #+#    #+#             */
/*   Updated: 2025/09/25 10:06:42 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	check_all_exist(t_data *data)
{
	return (data->no && data->so && data->we && data->ea && data->f >= 0
		&& data->c >= 0);
}

static int	process_after_identifiers(int fd, t_data *data, int flag)
{
	if (!check_all_exist(data) || flag)
	{
		ft_perror("Invalid or duplicate identifiers or invalid texture");
		return (1);
	}
	if (read_map(fd, data))
		return (ft_perror(NULL), 1);
	if (!validate_map(data))
		return (1);
	return (0);
}

int	parse_identifiers_and_map(int fd, t_data *data)
{
	char	*str;
	char	*tmp;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	str = NULL;
	while (i == 0 || (i < 6 && str))
	{
		str = get_next_line(fd);
		tmp = skip_ws(str);
		if (*tmp != '\0' && *tmp != '\n')
		{
			if_process(data, tmp, &flag);
			i++;
		}
		free(str);
	}
	return (process_after_identifiers(fd, data, flag));
}

t_data	*parse_input(char *input)
{
	t_data	*data;
	int		fd;

	data = init_data(input, &fd);
	if (!data)
		ft_clean(-1, get_addr_t_game(NULL));
	if (parse_identifiers_and_map(fd, data))
	{
		close(fd);
		ft_clean(-1, get_addr_t_game(NULL));
	}
	close(fd);
	return (data);
}
