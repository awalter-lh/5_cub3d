/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awalter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:40:50 by awalter           #+#    #+#             */
/*   Updated: 2023/06/02 09:40:51 by awalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_mlx *mlx)
{
	char	*dst;

	mlx->pimg = mlx_new_image(mlx->mlx, 5, 5);
	mlx->addr = mlx_get_data_addr(mlx->pimg, &mlx->bpp, &mlx->ll, &mlx->endian);
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			dst = mlx->addr + (j * mlx->ll + i * (mlx->bpp / 8));
			*(unsigned int *)dst = 0x0000FF00;
		}
	}
}

void	draw_wall_brick(t_mlx *mlx)
{
	char	*dst;

	mlx->wimg1 = mlx_new_image(mlx->mlx, 10, 5);
	mlx->addr = mlx_get_data_addr(mlx->wimg1, &mlx->bpp, &mlx->ll, &mlx->endian);
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			dst = mlx->addr + (j * mlx->ll + i * (mlx->bpp / 8));
			*(unsigned int *)dst = mlx->map.wall_color;
		}
	}

	mlx->wimg2 = mlx_new_image(mlx->mlx, 10, 5);
	mlx->addr = mlx_get_data_addr(mlx->wimg2, &mlx->bpp, &mlx->ll, &mlx->endian);
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			dst = mlx->addr + (j * mlx->ll + i * (mlx->bpp / 8));
			*(unsigned int *)dst = 0x00888888;
		}
	}
}

int	close_window(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->bg);
	mlx_destroy_image(mlx->mlx, mlx->wimg1);
	mlx_destroy_image(mlx->mlx, mlx->wimg2);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}

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

void	init_screen(t_mlx *mlx)
{
	mlx->width = 900;
	mlx->length = 540;
	// mlx->bg = mlx_new_image(mlx->mlx, mlx->width, mlx->length);
	// mlx->addr = mlx_get_data_addr(mlx->bg, &mlx->bpp, &mlx->ll, &mlx->endian);
	// mlx = make_bg(mlx);

	mlx->bg = mlx_new_image(mlx->mlx, mlx->width, mlx->length);
	mlx->addr = mlx_get_data_addr(mlx->bg, &mlx->bpp, &mlx->ll, &mlx->endian);
	mlx = make_bg(mlx);
}

void	init_test_map(t_mlx *mlx)
{
	mlx->map.floor_color = 0x00000000;
	mlx->map.sky_color = 0x00FFFFFF;
	mlx->map.wall_color = 0x00AAAAAA;
	mlx->map.mapx = 8;
	mlx->map.mapy = 8;
	mlx->map.map = malloc(sizeof(char *) * 9);
	for (int i = 0; i < 9; i++)
		mlx->map.map[i] = malloc(sizeof(char) * 9);
	mlx->map.map[0] = "11111111";
	mlx->map.map[1] = "10100001";
	mlx->map.map[2] = "10100001";
	mlx->map.map[3] = "10100001";
	mlx->map.map[4] = "10000001";
	mlx->map.map[5] = "10000101";
	mlx->map.map[6] = "10000001";
	mlx->map.map[7] = "11111111";
	mlx->map.map[8] = NULL;
	mlx->player.px = 300;
	mlx->player.py = 300;
	mlx->player.pa = 0;
	mlx->player.pdx = cos(mlx->player.pa) * 5;
	mlx->player.pdy = sin(mlx->player.pa) * 5;
}

float	pythagore(float rx, float ry, float px, float py)
{
	return (sqrt((px - rx) * (px - rx) + (py - ry) * (py - ry)));
}

void	draw_wall(t_mlx *mlx, float dist, int index, int type)
{
	int	nb_brick;
	int	offset;
	int	i;

	dist = cos(mlx->player.pa - mlx->ray.ra) * dist;
	nb_brick = ((64 * mlx->length) / dist);
	offset = (mlx->length - nb_brick) / 2;
	nb_brick /= 5;
	i = 0;
	while (i < nb_brick)
	{
		if (type == 1)
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->wimg1, index * 10, (i * 5) + offset);
		else if (type == 2)
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->wimg2, index * 10, (i * 5) + offset);
		i++;
	}
}

void	draw_ray(t_mlx *mlx)
{
	int		i;
	float	htan;
	float	vtan;
	float	hdist;
	float	hx;
	float	hy;
	float	final_dist;

	i = 0;
	mlx->ray.ra = mlx->player.pa - (PI / 4);
	if (mlx->ray.ra < 0)
		mlx->ray.ra += 2 * PI;
	else if (mlx->ray.ra > 2 * PI)
		mlx->ray.ra -= 2 * PI;
	while (i <= 90)
	{
		if (mlx->ray.ra < 0)
			mlx->ray.ra += 2 * PI;
		else if (mlx->ray.ra > 2 * PI)
			mlx->ray.ra -= 2 * PI;
		hdist = 10000000000;
		//---------Horizontal Check
		mlx->ray.dof = 0;
		htan = -1 / tan(mlx->ray.ra);
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
		hx = mlx->ray.rx;
		hy = mlx->ray.ry;
		while (mlx->ray.dof >= 0)
		{
			mlx->ray.mx = (int) (hx) >> 6;
			mlx->ray.my = (int) (hy) >> 6;
			hdist = pythagore(mlx->player.px, mlx->player.py, hx, hy);
			if (mlx->ray.mx < 0 || mlx->ray.mx >= mlx->map.mapx
				|| mlx->ray.my < 0 || mlx->ray.my >= mlx->map.mapy)
				mlx->ray.dof = -1;
			else if ((mlx->ray.mx < mlx->map.mapx || mlx->ray.my < mlx->map.mapy)
				&& mlx->map.map[mlx->ray.my][mlx->ray.mx] == '1')
				mlx->ray.dof = -1;
			else
			{
				hx += mlx->ray.xo;
				hy += mlx->ray.yo;
			}
		}
		
		//---------Vertical Check
		mlx->ray.dof = 0;
		vtan = -tan(mlx->ray.ra);
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
		while (mlx->ray.dof >= 0)
		{
			mlx->ray.mx = (int) (mlx->ray.rx) >> 6;
			mlx->ray.my = (int) (mlx->ray.ry) >> 6;
			if (mlx->ray.mx < 0 || mlx->ray.mx >= mlx->map.mapx
				|| mlx->ray.my < 0 || mlx->ray.my >= mlx->map.mapy)
				mlx->ray.dof = -1;
			else if ((mlx->ray.mx < mlx->map.mapx || mlx->ray.my < mlx->map.mapy)
				&& mlx->map.map[mlx->ray.my][mlx->ray.mx] == '1')
				mlx->ray.dof = -1;
			else
			{
				mlx->ray.rx += mlx->ray.xo;
				mlx->ray.ry += mlx->ray.yo;
			}
		}
		if (hdist > pythagore(mlx->player.px, mlx->player.py, mlx->ray.rx, mlx->ray.ry))
		{
			final_dist = pythagore(mlx->player.px, mlx->player.py, mlx->ray.rx, mlx->ray.ry);
			draw_wall(mlx, final_dist, i, 1);
		}
		else
		{
			final_dist = hdist;
			draw_wall(mlx, final_dist, i, 2);
		}
		mlx->ray.ra += 0.0174533;
		i++;
	}
}

void	player_move(t_mlx *mlx, int key)
{
	float	t_an;

	if (key == 'w')
	{
		t_an = mlx->player.pa;
		mlx->player.px += cos(t_an) * 5;
		mlx->player.py += sin(t_an) * 5;
	}
	else if (key == 'a')
	{
		t_an = mlx->player.pa + PI2;
		mlx->player.px += cos(t_an) * 5;
		mlx->player.py += sin(t_an) * 5;
	}
	else if (key == 's')
	{
		t_an = mlx->player.pa + PI;
		mlx->player.px += cos(t_an) * 5;
		mlx->player.py += sin(t_an) * 5;
	}
	else if (key == 'd')
	{
		t_an = mlx->player.pa + PI3;
		mlx->player.px += cos(t_an) * 5;
		mlx->player.py += sin(t_an) * 5;
	}
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
		if (mlx->player.pa < 0)
			mlx->player.pa += 2 * PI;
		mlx->player.pdx = cos(mlx->player.pa) * 5;
		mlx->player.pdy = sin(mlx->player.pa) * 5;
	}
	else if (key == 65363)
	{
		mlx->player.pa += 0.0174533 * 4;
		if (mlx->player.pa > 2 * PI)
			mlx->player.pa -= 2 * PI;
		mlx->player.pdx = cos(mlx->player.pa) * 5;
		mlx->player.pdy = sin(mlx->player.pa) * 5;
	}
	else
		return (0);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->bg, 0, 0);
	draw_ray(mlx);
	return (0);
}

int	main(void)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	init_test_map(&mlx);
	init_screen(&mlx);
	mlx.mlx_win = mlx_new_window(mlx.mlx, mlx.width, mlx.length, "Cub3d");
	mlx_hook(mlx.mlx_win, 2, 1, &key_event, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0, &close_window, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.bg, 0, 0);
	// mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, 0, 0);
	draw_wall_brick(&mlx);
	draw_ray(&mlx);
	mlx_loop(mlx.mlx);
}
