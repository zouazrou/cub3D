#include "get_line/get_next_line.h"
#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		C;
	int		F;
	int		player_x;
	int		player_y;
	int		player_d;
	char	**map;
}			t_data;

int after_last_line(t_data *data){
	int i = 0,j = 0;
		while(data->map[i] && data->map[i][0] == '\n')
			i++;
		while(data->map[i] && data->map[i][0] != '\n')
			i++;
		while(data->map[i] && data->map[i][0] == '\n')
			i++;
	if((data->map[i]) && (data->map[i][0] != '\0' && data->map[i][0] != '\n'))
		return 1;
	return 0;
}
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
void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->NO)
		free(data->NO);
	if (data->SO)
		free(data->SO);
	if (data->WE)
		free(data->WE);
	if (data->EA)
		free(data->EA);
	if (data->map)
		free_str_array(data->map);
	g_next_line(-1);
	free(data);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

void	data_init(t_data *data)
{
	data->NO = NULL;
	data->SO = NULL;
	data->WE = NULL;
	data->EA = NULL;
	data->C = -1;
	data->F = -1;
	data->player_d = -1;
	data->player_x = -1;
	data->player_y = -1;
	data->map = NULL;
}
int	is_color_line(char *s)
{
	s = skip_ws(s);
	return (*s == 'F' || *s == 'C');
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
static int	validate_rgb_part(char *part, int *value)
{
	char	*trimmed;

	if (!part)
		return (0);
	trimmed = ft_strtrim(part, "\n\r\t ");
	if (!trimmed)
		return (0);
	if (!is_all_digits(trimmed))
		return (free(trimmed), 0);
	*value = ft_atoi(trimmed);
	if (*value < 0 || *value > 255)
		return (free(trimmed), 0);
	free(trimmed);
	return (1);
}

void	parse_color(char *color, t_data *data)
{
	char	**str;
	int		rgb[3];

	color = skip_ws(color);
	if (color[0] != 'F' && color[0] != 'C')
		return ;
	str = ft_split(color + 1, ',');
	if (!str)
		return ;
	if (!validate_rgb_part(str[0], &rgb[0]) || !validate_rgb_part(str[1],
			&rgb[1]) || !validate_rgb_part(str[2], &rgb[2]) || str[3])
	{
		free_str_array(str);
		return ;
	}
	if (color[0] == 'F' && data->F < 0)
		data->F = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	else if (color[0] == 'C' && data->C < 0)
		data->C = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	free_str_array(str);
}

int	check_all_exist(t_data *data)
{
	return (data->NO && data->SO && data->WE && data->EA && data->F >= 0
		&& data->C >= 0);
}
char	**my_realloc(char **old, int old_size)
{
	char	**new_mem;
	int		i;

	i = 0;
	new_mem = malloc(sizeof(char *) * (old_size + 2));
	if (!new_mem)
		return (NULL);
	while (i < old_size)
	{
		new_mem[i] = old[i];
		i++;
	}
	free(old);
	return (new_mem);
}

int	read_map(int fd, t_data *data)
{
	int		count;
	char	*line;

	count = 0;
	while ((line = g_next_line(fd)))
	{
		char *x = skip_ws(line);
		if((ft_strlen(x) == 1 && x[0] == '\n') && (count == 0)){
			free(line);
			line = NULL;
			continue;
		}
		if (!data->map)
		{
			data->map = malloc(sizeof(char *) * 2);
			if (!data->map)
				return (1);
			data->map[0] = line;
			data->map[1] = NULL;
			count = 1;
			continue ;
		}
		data->map = my_realloc(data->map, count);
		if (!data->map)
			return (free(line), 1);
		data->map[count++] = line;
		data->map[count] = NULL;
	}
	return (0);
}
int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == '\n');
}
//strlen
int	check_neighbors(char **map, int y, int x)
{
	int	dy[4] = {-1, 1, 0, 0};
	int	dx[4] = {0, 0, -1, 1};
	int	i;
	int	ny;
	int	nx;

	i= 0;
	while (i < 4)
	{
		ny = y + dy[i];
		nx = x + dx[i];
		if (ny < 0 || nx < 0 || !map[ny] || nx >= (int)ft_strlen(map[ny]))
			return (0);
		if (map[ny][nx] == ' ' || map[ny][nx] == '\n' || map[ny][nx] == '\0')
			return (0);
		i++;
	}
	return (1);
}

int	validate_map(t_data *data)
{
	int		y;
	int		x;
	int		player_found;
	int		flag;
	char	c;

	y = 0;
	player_found = 0;
	flag = 0;
	if (!data->map || !data->map[0])
		return (write(2, "Error: Empty map\n", 17), 0);
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			c = data->map[y][x];
			if (!is_valid_char(c))
				return (write(2, "Error: Invalid char in map\n", 27), 0);
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				if (!check_neighbors(data->map, y, x))
					return (write(2, "Error: Map not closed\n", 22), 0);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (player_found)
					return (write(2, "Error: More than one player\n", 28), 0);
				data->player_x = x;
				data->player_y = y;
				data->player_d = c;
				player_found = 1;
			}
			x++;
		}
		y++;
	}
	if (!player_found)
		return (write(2, "Error: No player in map\n", 24), 0);
	if(after_last_line(data))
		return(0);
	return (1);
}
static void	assign_texture(char **dst, char *path, int *flag)
{
	if (*dst)
	{
		*flag = 1;
		return ;
	}
	int i = ft_strlen(skip_ws(path));

	if(path[i] == '\n')
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
// int check_file_exiest(t_data *data){
// 	int arr[4];
// 	int i = 0;
// 	while (i < 4)
// 		arr[i++] = -1;
// 	arr[0] = open(data->EA, O_RDONLY);
// 	arr[1] = open(data->WE, O_RDONLY);
// 	arr[2] = open(data->NO, O_RDONLY);
// 	arr[3] = open(data->SO, O_RDONLY);
// 	i = 0;
// 	while (i < 4)
// 	{
// 		if (arr[i] < 0)
// 		{
// 			while (--i >= 0)
// 				close(arr[i]);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }
int is_dot_cub(const char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	return (len > 4 && !ft_strncmp(filename + len - 4, ".cub", 4));
}
static t_data	*init_data(char *input, int *fd)
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

static int	parse_identifiers_and_map(int fd, t_data *data)
{
	char	*str;
	char	*tmp;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (i < 6 && (str = g_next_line(fd)))
	{
		tmp = skip_ws(str);
		if (*tmp != '\0' && *tmp != '\n')
		{
			if_process(data, tmp, &flag);
			i++;
		}
		free(str);
	}
	if (!check_all_exist(data) || flag)
		return (print_error("Error: Invalid or duplicate identifiers\n", 0), 1);
	if (read_map(fd, data))
		return (print_error("map malloc failed\n", 0), 1);
	if (!validate_map(data))
		return (1);
	// if (!check_file_exiest(data))
	// 	return (print_error("Error:Texture file not found\n", 0), 1);
	return (0);
}

t_data	*parse_input(char *input)
{
	t_data	*data;
	int		fd;

	data = init_data(input, &fd);
	if (!data)
		return (NULL);
	if (parse_identifiers_and_map(fd, data))
		return (close(fd), free_data(data), NULL);
	close(fd);
	return (data);
}


int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	data = parse_input(argv[1]);
	if (!data)
	{
		fprintf(stderr, "Failed to parse map or map invalid.\n");
		return (1);
	}
	printf("Textures:\n");
	printf("NO: %s\n", data->NO);
	printf("SO: %s\n", data->SO);
	printf("WE: %s\n", data->WE);
	printf("EA: %s\n", data->EA);
	printf("Colors:\n");
	printf("F: %06X\n", data->F);
	printf("C: %06X\n", data->C);
	printf("Player:\n");
	printf("Position: (%d, %d)\n", data->player_x, data->player_y);
	printf("Direction: %c\n", data->player_d);
	printf("Map:");
	for (int i = 0; data->map[i]; i++)
		printf("%s\n", data->map[i]);
	free_data(data);
	return (0);
}
