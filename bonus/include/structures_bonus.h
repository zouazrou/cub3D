/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:41:55 by zouazrou          #+#    #+#             */
/*   Updated: 2025/09/25 10:07:40 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H

typedef long long	t_ms;

typedef enum e_dir
{
	NORTH = 1,
	SOUTH,
	EAST,
	WEST,
}					t_dir;

typedef enum e_axis
{
	VERTICAL = 10,
	HORIZONTAL,
}					t_axis;

typedef struct s_vd
{
	double			x;
	double			y;
}					t_vd;

typedef struct s_player
{
	t_vd			position;
	double			angle;

	double			move_speed;
	double			rotation_speed;
}					t_player;

typedef struct s_ray
{
	int				color;
	double			angle;
	t_vd			inter;
	double			distance;
	bool			hit_wall;
	t_vd			inc;
	t_dir			side;
	t_axis			axis;
}					t_ray;

typedef struct s_img
{
	void			*img;
	char			*pixels;
	int				bpp;
	int				line;
	int				endian;
}					t_img;

typedef struct s_texture
{
	int				w;
	int				h;
	t_img			image;
	char			*filename;
}					t_texture;

typedef struct s_data_tex
{
	int				x;
	int				y;
	int				tex_x;
	int				tex_y;
	int				color;
	double			tex_step;
	double			tex_pos;
	t_texture		*texture;
}					t_data_tex;

typedef struct s_game
{
	void			*mlx;
	void			*win_3d;
	t_img			img;

	t_texture		north;
	t_texture		south;
	t_texture		west;
	t_texture		east;
	int				floor_color;
	int				ceiling_color;

	char			**map;
	int				mapy;
	int				width;
	int				height;
	int				tilesz;

	t_player		ply;
	double			fov;
	int				resolution;
	int				num_rays;
	t_ray			*ray;
	double			distance_to_plane;
}					t_game;

typedef struct s_data
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				c;
	int				f;
	int				player_x;
	int				player_y;
	int				player_d;
	int				map_y;
	char			**map;
}					t_data;

#endif