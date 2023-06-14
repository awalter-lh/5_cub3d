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
	mlx_destroy_image(mlx->mlx, mlx->img1);
	mlx_destroy_image(mlx->mlx, mlx->img2);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}

void	init_test_map(t_mlx *mlx)
{
	int	i;

	i = -1;
	mlx->map.floor_color = 0x00000000;
	mlx->map.sky_color = 0x00FFFFFF;
	mlx->map.wall_color = 0x00AAAAAA;
	mlx->map.mapx = 15;
	mlx->map.mapy = 10;
	mlx->map.map = malloc(sizeof(char *) * 11);
	while (++i < 11)
		mlx->map.map[i] = malloc(sizeof(char) * 16);
	mlx->map.map[0] = "      111      ";
	mlx->map.map[1] = "     10101     ";
	mlx->map.map[2] = "     10001     ";
	mlx->map.map[3] = "     10001     ";
	mlx->map.map[4] = "     10001     ";
	mlx->map.map[5] = "    1100011    ";
	mlx->map.map[6] = "  11100000111  ";
	mlx->map.map[7] = " 1100011100011 ";
	mlx->map.map[8] = "1110011 1100111";
	mlx->map.map[9] = "  1111   1111  ";
	mlx->map.map[10] = NULL;
	mlx->player.px = 400; // pos * 64 + 32
	mlx->player.py = 300;
	mlx->player.pa = 0; // N = PI3; S = PI2; E = 0; W = PI
	mlx->player.pdx = cos(mlx->player.pa) * 5;
	mlx->player.pdy = sin(mlx->player.pa) * 5;
}

void	init_screen(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	init_test_map(mlx);
	mlx->width = 1170;
	mlx->length = 540;
	mlx->bg = mlx_new_image(mlx->mlx, mlx->width, mlx->length);
	mlx->addr = mlx_get_data_addr(mlx->bg, &mlx->bpp, &mlx->ll, &mlx->endian);
	mlx = make_bg(mlx);
	mlx->mlx_win = mlx_new_window(mlx->mlx, mlx->width, mlx->length, "Cub3d");
	mlx->mlx_map = mlx_new_window(mlx->mlx,
			mlx->map.mapx * 16, mlx->map.mapy * 16, "MiniMap");
	mlx_hook(mlx->mlx_win, 2, 1, &key_event, mlx);
	mlx_hook(mlx->mlx_map, 2, 1, &key_event, mlx);
	mlx_mouse_move(mlx->mlx, mlx->mlx_win, mlx->width / 2, mlx->length / 2);
	mlx_mouse_hide(mlx->mlx, mlx->mlx_win);
	mlx_hook(mlx->mlx_win, 6, 1L << 6, &mouse_event, mlx);
	mlx_hook(mlx->mlx_win, 17, 0, &close_window, mlx);
	mlx_hook(mlx->mlx_map, 17, 0, &close_window, mlx);
	map_wallimg(mlx);
	map_playerimg(mlx);
	make_minimap(mlx);
}

int	main(void)
{
	t_mlx	mlx;

	init_screen(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.bg, 0, 0);
	draw_wall_brick(&mlx);
	draw_ray(&mlx);
	mlx_loop(mlx.mlx);
}
