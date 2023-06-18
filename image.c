/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awalter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:37:16 by awalter           #+#    #+#             */
/*   Updated: 2023/06/05 18:37:18 by awalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compare_buffs(t_mlx *mlx)
{
	int		x;
	int		y;
	char	*dst;

	y = 0;
	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			if (mlx->buff[y][x] != mlx->t_buff[y][x])
			{
				mlx->buff[y][x] = mlx->t_buff[y][x];
				dst = mlx->game_img->data + (y * mlx->game_img->size_line + x * (mlx->game_img->bpp / 8));
				*(unsigned int *)dst = mlx->buff[y][x];
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->game_img, 0, 0);
}

t_mlx	*make_game_img(t_mlx *mlx)
{
	int		i;
	int		j;

	i = 0;
	while (i < mlx->width)
	{
		j = 0;
		while (j < mlx->height / 2)
		{
			mlx->t_buff[j][i] = 0x00FFFFFF;
			j++;
		}
		while (j < mlx->height)
		{
			mlx->t_buff[j][i] = 0x00000000;
			j++;
		}
		i++;
	}
	return (mlx);
}

void	draw_wall_brick(t_mlx *mlx)
{
	char	*dst;
	int		i;
	int		j;

	i = -1;
	mlx->img1 = mlx_new_image(mlx->mlx, 13, 20);
	while (++i < 13)
	{
		j = -1;
		while (++j < 20)
		{
			dst = mlx->img1->data + (j * mlx->img1->size_line + i * (mlx->img1->bpp / 8));
			*(unsigned int *)dst = mlx->map.wall_color;
		}
	}
	mlx->img2 = mlx_new_image(mlx->mlx, 13, 20);
	i = -1;
	while (++i < 13)
	{
		j = -1;
		while (++j < 20)
		{
			dst = mlx->img2->data + (j * mlx->img2->size_line + i * (mlx->img2->bpp / 8));
			*(unsigned int *)dst = 0x00888888;
		}
	}
}

int	get_wall_color(t_mlx *mlx, t_wall wall, int y)
{
	int		ray_x;
	int		ray_y;
	int		wall_part_x;
	int		wall_part_y;

	ray_x = mlx->player.px + cos((mlx->player.pa - mlx->ray.ra)) * wall.dist;
	ray_y = mlx->player.py + sin((mlx->player.pa - mlx->ray.ra)) * wall.dist;
	ray_x = ray_x % 64;
	ray_y = ray_y % 64;
	if (wall.texture == 'N')
	{
		wall_part_x = ((float)mlx->map.n_texture.nb_row / 64) * ray_y;
		wall_part_y = (float)mlx->map.n_texture.nb_colomn / wall.height * y;
		return (mlx->map.n_texture.mat[wall_part_y][wall_part_x]);
	}
	else if (wall.texture == 'S')
	{
		wall_part_x = ((float)mlx->map.s_texture.nb_row / 64) * ray_y;
		wall_part_y = (float)mlx->map.s_texture.nb_colomn / wall.height * y;
		return (mlx->map.s_texture.mat[wall_part_y][wall_part_x]);
	}
	else if (wall.texture == 'E')
	{
		wall_part_x = ((float)mlx->map.e_texture.nb_row / 64) * ray_x;
		wall_part_y = (float)mlx->map.e_texture.nb_colomn / wall.height * y;
		return (mlx->map.e_texture.mat[wall_part_y][wall_part_x]);
	}
	else
	{
		wall_part_x = ((float)mlx->map.w_texture.nb_row / 64) * ray_x;
		wall_part_y = (float)mlx->map.w_texture.nb_colomn / wall.height * y;
		return (mlx->map.w_texture.mat[wall_part_y][wall_part_x]);
	}
}

void	fill_temp_buffer(t_mlx *mlx, t_wall wall, int index)
{
	int	y;

	y = 0;
	while (y < mlx->height)
	{
		if (y < wall.offset)
			mlx->t_buff[y][index] = mlx->map.sky_color;
		else if (y < (wall.height + wall.offset))
			mlx->t_buff[y][index] = get_wall_color(mlx, wall, y - wall.offset);
		else
			mlx->t_buff[y][index] = mlx->map.floor_color;
		y++;
	}
}

void	draw_wall(t_mlx *mlx, float dist, int index, int type)
{
	t_wall	wall;

	wall.dist = dist;
	dist = cos(mlx->player.pa - mlx->ray.ra) * dist;
	wall.height = ((64 * mlx->height) / dist);
	if (wall.height > mlx->height)
		wall.height = mlx->height;
	wall.offset = (mlx->height - wall.height) / 2;
	if (type == 1)
	{
		if (PI2 < mlx->ray.ra && mlx->ray.ra < PI3)
			wall.texture = 'W';
		else
			wall.texture = 'E';
	}
	else if (type == 2)
	{
		if (mlx->ray.ra < PI)
			wall.texture = 'S';
		else
			wall.texture = 'N';
	}
	fill_temp_buffer(mlx, wall, index);
}
