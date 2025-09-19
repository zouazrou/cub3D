/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:27:43 by melayyad          #+#    #+#             */
/*   Updated: 2025/09/18 18:40:55 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*own_strdup(const char *s);
char	*own_strjoin(char *s1, char *s2);
char	*own_strchr(const char *str, char c);
int		own_strlen(const char *str, char c);
char	*own_strcpy(const char *src, char c);

#endif
