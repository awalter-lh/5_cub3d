/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awalter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:01:18 by awalter           #+#    #+#             */
/*   Updated: 2023/06/22 14:01:19 by awalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	texture_n(t_mlx *mlx, t_wall wall, int ray_x)
{
	float	wall_part_x;
	float	wall_part_y;

	wall_part_y = ((float)mlx->map.n_texture->nb_row / (float)wall.real_height);
	wall_part_y *= (wall.y + ((wall.real_height - wall.height) / 2));
	wall_part_x = ((float)mlx->map.n_texture->nb_colomn / 64) * ray_x;
	return (mlx->map.n_texture->mat[(int)wall_part_y][(int)wall_part_x]);
}

int	texture_s(t_mlx *mlx, t_wall wall, int ray_x)
{
	float	wall_part_x;
	float	wall_part_y;

	wall_part_y = ((float)mlx->map.s_texture->nb_row / (float)wall.real_height);
	wall_part_y *= (wall.y + ((wall.real_height - wall.height) / 2));
	wall_part_x = ((float)mlx->map.s_texture->nb_colomn / 64) * ray_x;
	return (mlx->map.s_texture->mat[(int)wall_part_y][(int)wall_part_x]);
}

int	texture_e(t_mlx *mlx, t_wall wall, int ray_y)
{
	float	wall_part_x;
	float	wall_part_y;

	wall_part_y = ((float)mlx->map.e_texture->nb_row / (float)wall.real_height);
	wall_part_y *= (wall.y + ((wall.real_height - wall.height) / 2));
	wall_part_x = ((float)mlx->map.e_texture->nb_colomn / 64) * ray_y;
	return (mlx->map.e_texture->mat[(int)wall_part_y][(int)wall_part_x]);
}

int	texture_w(t_mlx *mlx, t_wall wall, int ray_y)
{
	float	wall_part_x;
	float	wall_part_y;

	wall_part_y = ((float)mlx->map.w_texture->nb_row / (float)wall.real_height);
	wall_part_y *= (wall.y + ((wall.real_height - wall.height) / 2));
	wall_part_x = ((float)mlx->map.w_texture->nb_colomn / 64) * ray_y;
	return (mlx->map.w_texture->mat[(int)wall_part_y][(int)wall_part_x]);
}

int	get_wall_color(t_mlx *mlx, t_wall wall, int y)
{
	int		ray_x;
	int		ray_y;

	wall.y = y;
	ray_x = mlx->player.px + (cos(mlx->ray.ra) * wall.dist);
	ray_y = mlx->player.py + (sin(mlx->ray.ra) * wall.dist);
	ray_x = ray_x % 64;
	ray_y = ray_y % 64;
	if (wall.texture == 'N')
		return (texture_n(mlx, wall, ray_x));
	else if (wall.texture == 'S')
		return (texture_s(mlx, wall, ray_x));
	else if (wall.texture == 'E')
		return (texture_e(mlx, wall, ray_y));
	else
		return (texture_w(mlx, wall, ray_y));
}
