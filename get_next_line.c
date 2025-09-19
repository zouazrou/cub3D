/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:02:31 by melayyad          #+#    #+#             */
/*   Updated: 2025/09/18 18:41:19 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_new_line_detector(char *str)
{
	char	*newline;

	if (!str)
		return (NULL);
	newline = own_strchr(str, '\n');
	if (newline)
		return (own_strdup(newline + 1));
	return (NULL);
}

static char	*read_until_newline(int fd, char *buffer)
{
	char	*here;
	ssize_t	bytes_read;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	here = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!here)
		return (NULL);
	while (!own_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, here, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(here), NULL);
		if (bytes_read == 0)
			break ;
		here[bytes_read] = '\0';
		buffer = own_strjoin(buffer, here);
	}
	free(here);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*here;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (fd < 0)
			free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_until_newline(fd, buffer);
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	here = own_strcpy(buffer, '\n');
	temp = ft_new_line_detector(buffer);
	free(buffer);
	buffer = temp;
	return (here);
}
