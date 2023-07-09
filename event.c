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

int	player_move(t_mlx *mlx, int key)
{
	float	t_an;
	int		new_x;
	int		new_y;

	t_an = mlx->player.pa;
	if (key == 'a')
		t_an += PI3;
	else if (key == 's')
		t_an += PI;
	else if (key == 'd')
		t_an += PI2;
	new_x = mlx->player.px + cos(t_an) * 5;
	new_y = mlx->player.py + sin(t_an) * 5;
	if (!(mlx->map.map[(new_y) >> 6][(new_x) >> 6] == '1'
		|| mlx->map.map[(new_y) >> 6][(new_x) >> 6] == '2'))
	{
		mlx->player.px = new_x;
		mlx->player.py = new_y;
		mlx_clear_window(mlx->mlx, mlx->mlx_map);
		make_minimap(mlx);
		return (1);
	}
	write(1, "\a", 1);
	return (0);
}

int	mouse_event(int x, int y, t_mlx *mlx)
{
	int	stat_x;

	(void) y;
	stat_x = mlx->width / 2;
	if (x < stat_x - 5)
		mlx->player.pa -= 0.0174533 * 2.2;
	else if (x > stat_x + 5)
		mlx->player.pa += 0.0174533 * 2.2;
	mlx->player.pa = fix_angle(mlx->player.pa);
	if (stat_x - 5 <= x && x <= stat_x + 5)
		return (1);
	mlx_mouse_move(mlx->mlx, mlx->mlx_win, mlx->width / 2, mlx->height / 2);
	mlx->player.pdx = cos(mlx->player.pa) * 5;
	mlx->player.pdy = sin(mlx->player.pa) * 5;
	draw_ray(mlx);
	return (0);
}

int	open_door(int key, t_mlx *mlx)
{
	int	new_x;
	int	new_y;

	if (key != ' ')
		return (0);
	new_x = mlx->player.px + cos(mlx->player.pa) * 65;
	new_y = mlx->player.py + sin(mlx->player.pa) * 65;
	if (mlx->map.map[(new_y) >> 6][(new_x) >> 6] == '2')
		mlx->map.map[(new_y) >> 6][(new_x) >> 6] = '3';
	else if (mlx->map.map[(new_y) >> 6][(new_x) >> 6] == '3')
		mlx->map.map[(new_y) >> 6][(new_x) >> 6] = '2';
	else
		return (0);
	return (1);
}

int	key_event(int key, t_mlx *mlx)
{
	if (key == 65307)
		close_window(mlx);
	if (key == 'w' || key == 'a' || key == 's' || key == 'd')
	{
		if (!player_move(mlx, key))
			return (0);
	}
	else if (key == 65361)
	{
		mlx->player.pa -= 0.0174533 * 4;
		mlx->player.pa = fix_angle(mlx->player.pa);
	}
	else if (key == 65363)
	{
		mlx->player.pa += 0.0174533 * 4;
		mlx->player.pa = fix_angle(mlx->player.pa);
	}
	else if (!open_door(key, mlx))
		return (0);
	mlx->player.pdx = cos(mlx->player.pa) * 5;
	mlx->player.pdy = sin(mlx->player.pa) * 5;
	draw_ray(mlx);
	return (0);
}
