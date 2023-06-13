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

t_mlx	*make_bg(t_mlx *mlx)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	while (i < mlx->width)
	{
		j = 0;
		while (j < mlx->length / 2)
		{
			dst = mlx->addr + (j * mlx->ll + i * (mlx->bpp / 8));
			*(unsigned int *)dst = mlx->map.sky_color;
			j++;
		}
		while (j < mlx->length)
		{
			dst = mlx->addr + (j * mlx->ll + i * (mlx->bpp / 8));
			*(unsigned int *)dst = mlx->map.floor_color;
			j++;
		}
		i++;
	}
	return (mlx);
}

void	map_playerimg(t_mlx *mlx)
{
	char	*dst;
	int		i;
	int		j;

	i = -1;
	mlx->pimg = mlx_new_image(mlx->mlx, 4, 4);
	mlx->addr = mlx_get_data_addr(mlx->pimg, &mlx->bpp, &mlx->ll, &mlx->endian);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			dst = mlx->addr + (j * mlx->ll + i * (mlx->bpp / 8));
			*(unsigned int *)dst = 0x00FF0000;
		}
	}
}

void	map_wallimg(t_mlx *mlx)
{
	char	*dst;
	int		i;
	int		j;

	i = -1;
	mlx->wimg = mlx_new_image(mlx->mlx, 16, 16);
	mlx->addr = mlx_get_data_addr(mlx->wimg, &mlx->bpp, &mlx->ll, &mlx->endian);
	while (++i < 16)
	{
		j = -1;
		while (++j < 16)
		{
			dst = mlx->addr + (j * mlx->ll + i * (mlx->bpp / 8));
			*(unsigned int *)dst = 0x00928672;
		}
	}
}

void	make_minimap(t_mlx *mlx)
{
	int	i;
	int	j;

	j = -1;
	while (++j < mlx->map.mapy)
	{
		i = -1;
		while (++i < mlx->map.mapx)
		{
			if (mlx->map.map[j][i] == '0')
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_mwin, mlx->wimg, i << 4, j << 4);
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_mwin, mlx->pimg, mlx->player.px >> 2, mlx->player.py >> 2);
}

void	draw_wall_brick(t_mlx *mlx)
{
	char	*dst;
	int		i;
	int		j;

	i = -1;
	mlx->img1 = mlx_new_image(mlx->mlx, 13, 20);
	mlx->addr = mlx_get_data_addr(mlx->img1, &mlx->bpp, &mlx->ll, &mlx->endian);
	while (++i < 13)
	{
		j = -1;
		while (++j < 20)
		{
			dst = mlx->addr + (j * mlx->ll + i * (mlx->bpp / 8));
			*(unsigned int *)dst = mlx->map.wall_color;
		}
	}
	mlx->img2 = mlx_new_image(mlx->mlx, 13, 20);
	mlx->addr = mlx_get_data_addr(mlx->img2, &mlx->bpp, &mlx->ll, &mlx->endian);
	i = -1;
	while (++i < 13)
	{
		j = -1;
		while (++j < 20)
		{
			dst = mlx->addr + (j * mlx->ll + i * (mlx->bpp / 8));
			*(unsigned int *)dst = 0x00888888;
		}
	}
}

void	draw_wall(t_mlx *mlx, float dist, int index, int type)
{
	int	nb_brick;
	int	offset;
	int	i;

	dist = cos(mlx->player.pa - mlx->ray.ra) * dist;
	nb_brick = ((64 * mlx->length) / dist);
	if (nb_brick > mlx->length)
		nb_brick = mlx->length;
	nb_brick /= 20;
	offset = (mlx->length - (nb_brick * 20)) / 2;
	i = 0;
	while (i < nb_brick)
	{
		if (type == 1)
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img1,
				index * 13, (i * 20) + offset);
		else if (type == 2)
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img2,
				index * 13, (i * 20) + offset);
		i++;
	}
}
