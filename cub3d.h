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
	t_xpm	n_texture;
	t_xpm	s_texture;
	t_xpm	e_texture;
	t_xpm	w_texture;
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
	t_img		*bg;
	t_img		*test;
	t_img		*pimg;
	t_img		*wimg;
	t_img		*img1;
	t_img		*img2;
	int			width;
	int			height;
	t_map		map;
	t_player	player;
	t_ray		ray;
}	t_mlx;

/******************************main.c*******************************/
int		close_window(t_mlx *mlx);
void	init_screen(t_mlx *mlx);
void	init_test_map(t_mlx *mlx);

/*****************************event.c*******************************/
float	fix_angle(float angle);
int		player_move(t_mlx *mlx, int key);
int		key_event(int key, t_mlx *mlx);
int		mouse_event(int x, int y, t_mlx *mlx);

/******************************ray.c********************************/
float	pythagore(float rx, float ry, float px, float py);
t_dist	common_wall_loop(t_mlx *mlx);
t_dist	horizontal_check(t_mlx *mlx, float htan);
t_dist	vertical_check(t_mlx *mlx, float vtan);
void	draw_ray(t_mlx *mlx);

/*****************************image.c*******************************/
t_mlx	*make_game_img(t_mlx *mlx);
void	draw_wall_brick(t_mlx *mlx);
void	draw_wall(t_mlx *mlx, float dist, int index, int type);
void	compare_buffs(t_mlx *mlx);

/****************************minimap.c******************************/
void	map_playerimg(t_mlx *mlx);
void	map_wallimg(t_mlx *mlx);
void	make_minimap(t_mlx *mlx);

#endif
