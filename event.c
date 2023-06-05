/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awalter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:40:00 by awalter           #+#    #+#             */
/*   Updated: 2023/06/05 18:40:02 by awalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	fix_angle(float angle)
{
	if (angle < 0)
		return (angle + 2 * PI);
	else if (angle > 2 * PI)
		return (angle - 2 * PI);
	return (angle);
}

void	player_move(t_mlx *mlx, int key)
{
	float	t_an;

	if (key == 'w')
		t_an = mlx->player.pa;
	else if (key == 'a')
		t_an = mlx->player.pa + PI3;
	else if (key == 's')
		t_an = mlx->player.pa + PI;
	else if (key == 'd')
		t_an = mlx->player.pa + PI2;
	mlx->player.px += cos(t_an) * 5;
	mlx->player.py += sin(t_an) * 5;
}

int	key_event(int key, t_mlx *mlx)
{
	if (key == 65307)
		close_window(mlx);
	if (key == 'w' || key == 'a' || key == 's' || key == 'd')
		player_move(mlx, key);
	else if (key == 65361)
	{
		mlx->player.pa -= 0.0174533 * 4;
		mlx->player.pa = fix_angle(mlx->player.pa);
		mlx->player.pdx = cos(mlx->player.pa) * 5;
		mlx->player.pdy = sin(mlx->player.pa) * 5;
	}
	else if (key == 65363)
	{
		mlx->player.pa += 0.0174533 * 4;
		mlx->player.pa = fix_angle(mlx->player.pa);
		mlx->player.pdx = cos(mlx->player.pa) * 5;
		mlx->player.pdy = sin(mlx->player.pa) * 5;
	}
	else
		return (0);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->bg, 0, 0);
	draw_ray(mlx);
	return (0);
}
