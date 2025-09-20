/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:40:32 by melayyad          #+#    #+#             */
/*   Updated: 2025/09/20 12:10:27 by zouazrou         ###   ########.fr       */
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

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
// 		i++;
// 	if (i == n)
// 		return (0);
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

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

char	*print_error(char *error, int flag)
{
	int	i;

	i = 0;
	if (flag)
	{
		perror(error);
		return (NULL);
	}
	else
	{
		while (error[i])
			write(2, &error[i++], 1);
	}
	return (NULL);
}
