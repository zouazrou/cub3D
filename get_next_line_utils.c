/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:20:48 by melayyad          #+#    #+#             */
/*   Updated: 2025/09/18 18:41:41 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	own_strlen(const char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*own_strchr(const char *str, char c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

char	*own_strdup(const char *s)
{
	size_t	len;
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	len = own_strlen(s, '\0');
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

char	*own_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*joined;
	size_t	i;

	if (!s1)
		s1 = own_strdup("");
	if (!s2)
		return (NULL);
	len1 = own_strlen(s1, '\0');
	len2 = own_strlen(s2, '\0');
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (i < len1 + len2)
	{
		if (i < len1)
			joined[i] = s1[i];
		else
			joined[i] = s2[i - len1];
		i++;
	}
	joined[len1 + len2] = '\0';
	return (free(s1), joined);
}

char	*own_strcpy(const char *src, char c)
{
	size_t	len;
	size_t	i;
	char	*dest;

	if (!src)
		return (NULL);
	len = own_strlen(src, c);
	dest = malloc(len + 2);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	if (src[i] == c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
