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
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define PI 3.1415926535
# define PI2 PI/2
# define PI3 3*PI/2

typedef struct s_map
{
	int		sky_color;
	int		floor_color;
	int		wall_color;
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

typedef struct s_mlx {
	void		*mlx;
	void		*mlx_win;
	void		*bg;
	void		*img;
	void		*pimg;
	void		*rimg1;
	void		*rimg2;
	char		*addr;
	int			bpp;
	int			ll;
	int			endian;
	int			width;
	int			length;
	t_map		map;
	t_player	player;
	t_ray		ray;
}	t_mlx;



#endif
