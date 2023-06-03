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

void	draw_ray_end(t_mlx *mlx)
{
	char	*dst;

	mlx->rimg1 = mlx_new_image(mlx->mlx, 5, 5);
	mlx->addr = mlx_get_data_addr(mlx->rimg1, &mlx->bpp, &mlx->ll, &mlx->endian);
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			dst = mlx->addr + (j * mlx->ll + i * (mlx->bpp / 8));
			*(unsigned int *)dst = 0x00FF0000;
		}
	}

	mlx->rimg2 = mlx_new_image(mlx->mlx, 5, 5);
	mlx->addr = mlx_get_data_addr(mlx->rimg2, &mlx->bpp, &mlx->ll, &mlx->endian);
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			dst = mlx->addr + (j * mlx->ll + i * (mlx->bpp / 8));
			*(unsigned int *)dst = 0x000000FF;
		}
	}
}

int	close_window(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_image(mlx->mlx, mlx->pimg);
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
			*(unsigned int *)dst = 0x000EEEEEE;
			j++;
		}
		while (j < mlx->length)
		{
			dst = mlx->addr + (j * mlx->ll + i * (mlx->bpp / 8));
			*(unsigned int *)dst = 0x000000000;
			j++;
		}
		i++;
	}
	return (mlx);
}

t_mlx	*make_img(t_mlx *mlx)
{
	int		i;
	int		j;
	int 	color;
	int		stopx;
	int		stopy;
	char	*dst;

	i = 0;
	while (i < mlx->width)
	{
		j = 0;
		stopx = 0;
		while (j < mlx->length)
		{
			stopy = 0;
			if (!stopx && !stopy && mlx->map.map[j / 64] && i / 64 < 9
				&& mlx->map.map[j / 64][i / 64] == '1')
				color = 0x000FFFFFF;
			else
			{
				if (!stopx && !mlx->map.map[j / 64])
					stopx = 1;
				if (!stopy && i / 64 > 8)
					stopy = 1;
				color = 0x000000000;
			}
			dst = mlx->addr + (j * mlx->ll + i * (mlx->bpp / 8));
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
	return (mlx);
}

void	init_screen(t_mlx *mlx)
{
	mlx->width = 960;
	mlx->length = 540;
	// mlx->bg = mlx_new_image(mlx->mlx, mlx->width, mlx->length);
	// mlx->addr = mlx_get_data_addr(mlx->bg, &mlx->bpp, &mlx->ll, &mlx->endian);
	// mlx = make_bg(mlx);

	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->length);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->ll, &mlx->endian);
	mlx = make_img(mlx);
}

void	init_test_map(t_mlx *mlx)
{
	mlx->map.floor_color = 0x000000000;
	mlx->map.sky_color = 0x000FFFFFF;
	mlx->map.wall_color = 0x000AAAAAA;
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

void	draw_ray(t_mlx *mlx)
{
	float	htan;
	float	vtan;
	float	hdist;
	float	hx;
	float	hy;

	mlx->ray.ra = mlx->player.pa - (PI / 4);
	while (mlx->ray.ra <= mlx->player.pa + (PI / 4))
	{
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
		while (mlx->ray.dof >= 0)
		{
			mlx->ray.mx = (int) (mlx->ray.rx) >> 6;
			mlx->ray.my = (int) (mlx->ray.ry) >> 6;
			hx = mlx->ray.rx;
			hy = mlx->ray.ry;
			hdist = pythagore(mlx->player.px, mlx->player.py, hx, hy);
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
		// printf("%f | %f\n", hdist, pythagore(mlx->player.px, mlx->player.py, mlx->ray.rx, mlx->ray.ry));
		if (hdist > pythagore(mlx->player.px, mlx->player.py, mlx->ray.rx, mlx->ray.ry))
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->rimg2, mlx->ray.rx, mlx->ray.ry);
		else
			mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->rimg1, hx, hy);
		mlx->ray.ra += 0.0174533;
	}
}

int	key_event(int key, t_mlx *mlx)
{
	if (key == 65307)
		close_window(mlx);
	if (key == 'w')
		mlx->player.py -= 5;
	else if (key == 's')
		mlx->player.py += 5;
	else if (key == 'd')
		mlx->player.px += 5;
	else if (key == 'a')
		mlx->player.px -= 5;
	else if (key == 65361)
	{
		mlx->player.pa -= 0.1;
		if (mlx->player.pa < 0)
			mlx->player.pa += 2 * PI;
		mlx->player.pdx = cos(mlx->player.pa) * 5;
		mlx->player.pdy = sin(mlx->player.pa) * 5;
	}
	else if (key == 65363)
	{
		mlx->player.pa += 0.1;
		if (mlx->player.pa > 2 * PI)
			mlx->player.pa -= 2 * PI;
		mlx->player.pdx = cos(mlx->player.pa) * 5;
		mlx->player.pdy = sin(mlx->player.pa) * 5;
	}
	else
		return (0);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->pimg, mlx->player.px, mlx->player.py);
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
	// mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.bg, 0, 0);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, 0, 0);
	draw_player(&mlx);
	draw_ray_end(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.pimg, mlx.player.px, mlx.player.py);
	draw_ray(&mlx);
	mlx_loop(mlx.mlx);
}
