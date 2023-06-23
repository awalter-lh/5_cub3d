/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awalter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:40:38 by awalter           #+#    #+#             */
/*   Updated: 2023/06/02 09:40:39 by awalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "./xpm_parser/xpm_parser.h"

# define PI 3.1415926535
# define PI2 PI/2
# define PI3 3*PI/2

typedef struct s_map
{
	int		sky_color;
	int		floor_color;
	int		wall_color;
	t_xpm	*n_texture;
	t_xpm	*s_texture;
	t_xpm	*e_texture;
	t_xpm	*w_texture;
	int		mapx;
	int		mapy;
	char	**map;
}	t_map;

typedef struct s_player
{
	int		px;
	int		py;
	float	pdx;
	float	pdy;
	float	pa;
}	t_player;

typedef struct s_ray
{
	int		r;
	int		mx;
	int		my;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
}	t_ray;

typedef struct s_dist
{
	float	x;
	float	y;
	float	dist;
}	t_dist;

typedef struct s_wall
{
	int		y;
	float	dist;
	int		offset;
	int		height;
	int		real_height;
	char	texture;
}	t_wall;

typedef struct s_mlx {
	void		*mlx;
	void		*mlx_win;
	void		*mlx_map;
	int			**buff;
	int			**t_buff;
	t_img		*game_img;
	t_img		*pimg;
	t_img		*wimg;
	t_img		*dimg;
	int			width;
	int			height;
	t_map		map;
	t_player	player;
	t_ray		ray;
}	t_mlx;

/*****************************cub3d.c*******************************/
void	init_test_map(t_mlx *mlx);
void	init_screen(t_mlx *mlx);
int		main(void);

/*****************************event.c*******************************/
float	fix_angle(float angle);
int		player_move(t_mlx *mlx, int key);
int		mouse_event(int x, int y, t_mlx *mlx);
int		open_door(int key, t_mlx *mlx);
int		key_event(int key, t_mlx *mlx);

/******************************ray.c********************************/
float	pythagore(float rx, float ry, float px, float py);
t_dist	common_wall_loop(t_mlx *mlx);
t_dist	horizontal_check(t_mlx *mlx, float htan);
t_dist	vertical_check(t_mlx *mlx, float vtan);
void	draw_ray(t_mlx *mlx);

/*****************************image.c*******************************/
void	compare_buffs(t_mlx *mlx);
t_mlx	*make_game_img(t_mlx *mlx);
void	fill_temp_buffer(t_mlx *mlx, t_wall wall, int index);
void	draw_wall(t_mlx *mlx, float dist, int index, int type);

/****************************minimap.c******************************/
void	map_playerimg(t_mlx *mlx);
void	map_wallimg(t_mlx *mlx);
void	map_doorimg(t_mlx *mlx);
void	make_minimap(t_mlx *mlx);

/**************************close_window.c***************************/
void	free_xpm_struct(t_xpm *xpm);
void	free_map(t_map map);
void	free_buff(t_mlx *mlx);
int		close_window(t_mlx *mlx);

/***************************wall_color.c****************************/
int		texture_n(t_mlx *mlx, t_wall wall, int ray_x);
int		texture_s(t_mlx *mlx, t_wall wall, int ray_x);
int		texture_e(t_mlx *mlx, t_wall wall, int ray_y);
int		texture_w(t_mlx *mlx, t_wall wall, int ray_y);
int		get_wall_color(t_mlx *mlx, t_wall wall, int y);

#endif
