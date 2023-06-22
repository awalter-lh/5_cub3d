/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awalter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:14:51 by awalter           #+#    #+#             */
/*   Updated: 2023/06/14 10:14:53 by awalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_playerimg(t_mlx *mlx)
{
	char	*dst;
	int		i;
	int		j;

	i = -1;
	mlx->pimg = mlx_new_image(mlx->mlx, 4, 4);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			dst = mlx->pimg->data;
			dst += j * mlx->pimg->size_line;
			dst += i * (mlx->pimg->bpp / 8);
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
	while (++i < 16)
	{
		j = -1;
		while (++j < 16)
		{
			dst = mlx->wimg->data;
			dst += j * mlx->wimg->size_line;
			dst += i * (mlx->wimg->bpp / 8);
			*(unsigned int *)dst = 0x00928672;
		}
	}
}

void	map_doorimg(t_mlx *mlx)
{
	char	*dst;
	int		i;
	int		j;

	i = -1;
	mlx->dimg = mlx_new_image(mlx->mlx, 12, 12);
	while (++i < 12)
	{
		j = -1;
		while (++j < 12)
		{
			dst = mlx->dimg->data;
			dst += j * mlx->dimg->size_line;
			dst += i * (mlx->dimg->bpp / 8);
			*(unsigned int *)dst = 0x00706450;
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
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_map, mlx->wimg,
					i << 4, j << 4);
			else if (mlx->map.map[j][i] == 'C' || mlx->map.map[j][i] == 'O')
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_map, mlx->dimg,
					(i << 4) + 2, (j << 4) + 2);
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_map, mlx->pimg,
		mlx->player.px >> 2, mlx->player.py >> 2);
}
