/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awalter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:34:25 by awalter           #+#    #+#             */
/*   Updated: 2023/06/05 18:34:29 by awalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	pythagore(float rx, float ry, float px, float py)
{
	return (sqrt((px - rx) * (px - rx) + (py - ry) * (py - ry)));
}

t_dist	common_wall_loop(t_mlx *mlx)
{
	t_dist	dist;

	dist.x = mlx->ray.rx;
	dist.y = mlx->ray.ry;
	dist.dist = 10000000000;
	while (mlx->ray.dof >= 0)
	{
		mlx->ray.mx = (int)(dist.x) >> 6;
		mlx->ray.my = (int)(dist.y) >> 6;
		dist.dist = pythagore(mlx->player.px, mlx->player.py, dist.x, dist.y);
		if (mlx->ray.mx < 0 || mlx->ray.mx >= mlx->map.mapx
			|| mlx->ray.my < 0 || mlx->ray.my >= mlx->map.mapy)
			mlx->ray.dof = -1;
		else if ((mlx->ray.mx < mlx->map.mapx || mlx->ray.my < mlx->map.mapy)
			&& mlx->map.map[mlx->ray.my][mlx->ray.mx] == '1')
			mlx->ray.dof = -1;
		else
		{
			dist.x += mlx->ray.xo;
			dist.y += mlx->ray.yo;
		}
	}
	return (dist);
}

t_dist	horizontal_check(t_mlx *mlx, float htan)
{
	if (mlx->ray.ra > PI)
	{
		mlx->ray.ry = (((int)mlx->player.py >> 6) << 6) - 0.0001;
		mlx->ray.rx = (mlx->player.py - mlx->ray.ry) * htan + mlx->player.px;
		mlx->ray.yo = -64;
		mlx->ray.xo = -mlx->ray.yo * htan;
	}
	else if (mlx->ray.ra < PI)
	{
		mlx->ray.ry = (((int)mlx->player.py >> 6) << 6) + 64;
		mlx->ray.rx = (mlx->player.py - mlx->ray.ry) * htan + mlx->player.px;
		mlx->ray.yo = 64;
		mlx->ray.xo = -mlx->ray.yo * htan;
	}
	else if (mlx->ray.ra == 0 || mlx->ray.ra == PI)
	{
		mlx->ray.rx = mlx->player.px;
		mlx->ray.ry = mlx->player.py;
		mlx->ray.dof = -1;
	}
	return (common_wall_loop(mlx));
}

t_dist	vertical_check(t_mlx *mlx, float vtan)
{
	if (mlx->ray.ra > PI2 && mlx->ray.ra < PI3)
	{
		mlx->ray.rx = (((int)mlx->player.px >> 6) << 6) - 0.0001;
		mlx->ray.ry = (mlx->player.px - mlx->ray.rx) * vtan + mlx->player.py;
		mlx->ray.xo = -64;
		mlx->ray.yo = -mlx->ray.xo * vtan;
	}
	else if (mlx->ray.ra < PI2 || mlx->ray.ra > PI3)
	{
		mlx->ray.rx = (((int)mlx->player.px >> 6) << 6) + 64;
		mlx->ray.ry = (mlx->player.px - mlx->ray.rx) * vtan + mlx->player.py;
		mlx->ray.xo = 64;
		mlx->ray.yo = -mlx->ray.xo * vtan;
	}
	else if (mlx->ray.ra == PI2 || mlx->ray.ra == PI3)
	{
		mlx->ray.ry = mlx->player.py;
		mlx->ray.rx = mlx->player.px;
		mlx->ray.dof = 8;
	}
	return (common_wall_loop(mlx));
}

void	draw_ray(t_mlx *mlx)
{
	int		i;
	float	htan;
	float	vtan;
	t_dist	h_dist;
	t_dist	v_dist;

	i = 0;
	mlx->ray.ra = mlx->player.pa - (PI / 4);
	mlx->ray.ra = fix_angle(mlx->ray.ra);
	while (i <= 90)
	{
		mlx->ray.ra = fix_angle(mlx->ray.ra);
		mlx->ray.dof = 0;
		htan = -1 / tan(mlx->ray.ra);
		h_dist = horizontal_check(mlx, htan);
		mlx->ray.dof = 0;
		vtan = -tan(mlx->ray.ra);
		v_dist = vertical_check(mlx, vtan);
		if (h_dist.dist > v_dist.dist)
			draw_wall(mlx, v_dist.dist, i, 1);
		else
			draw_wall(mlx, h_dist.dist, i, 2);
		mlx->ray.ra += 0.0174533;
		i++;
	}
}
