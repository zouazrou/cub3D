/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:40:32 by melayyad          #+#    #+#             */
/*   Updated: 2025/09/24 15:52:05 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_str_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}

char	*skip_ws(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

t_data	*get_addr_t_data(t_data *ptr)
{
	static t_data	*addr = NULL;

	if (ptr)
		addr = ptr;
	return (addr);
}

int	is_all_digits(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}
