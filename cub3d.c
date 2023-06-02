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

int	close_window(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->bg);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}

int	key_event(int key, t_mlx *mlx)
{
	if (key == 65307)
		close_window(mlx);
	return (0);
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

void	init_screen(t_mlx *mlx)
{
	mlx->width = 960;
	mlx->length = 540;
	mlx->bg = mlx_new_image(mlx->mlx, mlx->width, mlx->length);
	mlx->addr = mlx_get_data_addr(mlx->bg, &mlx->bpp, &mlx->ll, &mlx->endian);
	mlx = make_bg(mlx);
}

void	init_test_map(t_mlx *mlx)
{
	mlx->map.floor_color = 0x000000000;
	mlx->map.shy_color = 0x000FFFFFF;
	mlx->map.wall_color = 0x000AAAAAA;
	mlx->map.map = malloc(sizeof(char *) * 9);
	for (int i = 0; i < 9; i++)
		mlx->map.map[i] = malloc(sizeof(char) * 9);
	mlx->map.map[0] = "11111111";
	mlx->map.map[0] = "10100001";
	mlx->map.map[0] = "10100001";
	mlx->map.map[0] = "10100001";
	mlx->map.map[0] = "10000001";
	mlx->map.map[0] = "10000101";
	mlx->map.map[0] = "10000001";
	mlx->map.map[0] = "11111111";
	mlx->map.map[0] = NULL;
}

int	main(void)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	init_screen(&mlx);
	mlx.mlx_win = mlx_new_window(mlx.mlx, mlx.width, mlx.length, "Cub3d");
	mlx_key_hook(mlx.mlx_win, key_event, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0, &close_window, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.bg, 0, 0);
	mlx_loop(mlx.mlx);
}
