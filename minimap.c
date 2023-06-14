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
				mlx_put_image_to_window(mlx->mlx, mlx->mlx_map, mlx->wimg,
					i << 4, j << 4);
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_map, mlx->pimg,
		mlx->player.px >> 2, mlx->player.py >> 2);
}
