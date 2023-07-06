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

void	init_test_map(t_mlx *mlx)
{
	int	i;

	i = -1;
	mlx->map.floor_color = 0x00000000;
	mlx->map.sky_color = 0x00FFFFFF;
	mlx->map.n_texture = xpm_parsing("./textures/tile187.xpm");
	mlx->map.s_texture = xpm_parsing("./textures/tile187.xpm");
	mlx->map.e_texture = xpm_parsing("./textures/tile187.xpm");
	mlx->map.w_texture = xpm_parsing("./textures/tile187.xpm");
	mlx->map.mapx = 15;
	mlx->map.mapy = 10;
	mlx->map.map = malloc(sizeof(char *) * 11);
	while (++i < 10)
		mlx->map.map[i] = malloc(sizeof(char) * 16);
	ft_strlcpy(mlx->map.map[0], "011111111111111", 20);
	ft_strlcpy(mlx->map.map[1], "100000000000001", 20);
	ft_strlcpy(mlx->map.map[2], "100000000000001", 20);
	ft_strlcpy(mlx->map.map[3], "100000000000001", 20);
	ft_strlcpy(mlx->map.map[4], "100000000000001", 20);
	ft_strlcpy(mlx->map.map[5], "11O111000000001", 20);
	ft_strlcpy(mlx->map.map[6], "100001000000001", 20);
	ft_strlcpy(mlx->map.map[7], "10000C000000001", 20);
	ft_strlcpy(mlx->map.map[8], "100001000000001", 20);
	ft_strlcpy(mlx->map.map[9], "111111111111111", 20);
	mlx->map.map[10] = NULL;
	mlx->player.px = 96; // pos(x) * 64 + 32
	mlx->player.py = 96; // pos(y) * 64 + 32
	mlx->player.pa = 0; // N = PI3; S = PI2; E = 0; W = PI
	mlx->player.pdx = cos(mlx->player.pa) * 5;
	mlx->player.pdy = sin(mlx->player.pa) * 5;
}

void	init_screen(t_mlx *mlx)
{
	int	i;

	i = -1;
	mlx->mlx = mlx_init();
	mlx->width = 858;
	mlx->height = 540;
	mlx->buff = malloc(sizeof(int *) * (mlx->height + 1));
	mlx->t_buff = malloc(sizeof(int *) * (mlx->height + 1));
	if (!mlx->buff || !mlx->t_buff)
		exit (1);
	while (++i < mlx->height)
	{
		mlx->buff[i] = ft_calloc(sizeof(int), (mlx->width + 1));
		mlx->t_buff[i] = ft_calloc(sizeof(int), (mlx->width + 1));
		if (!mlx->buff[i] || !mlx->t_buff[i])
			exit(1);
	}
	mlx->buff[i] = NULL;
	init_test_map(mlx); // to remove
	mlx->mlx_win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "Cub3d");
	mlx->game_img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx = make_game_img(mlx);
	mlx->mlx_map = mlx_new_window(mlx->mlx,
			mlx->map.mapx * 16, mlx->map.mapy * 16, "MiniMap");
}

int	main(void)
{
	t_mlx	mlx;

	init_screen(&mlx);
	mlx_hook(mlx.mlx_win, 2, 1, &key_event, &mlx);
	mlx_hook(mlx.mlx_map, 2, 1, &key_event, &mlx);
	mlx_mouse_move(mlx.mlx, mlx.mlx_win, mlx.width / 2, mlx.height / 2);
	mlx_mouse_hide(mlx.mlx, mlx.mlx_win);
	mlx_hook(mlx.mlx_win, 6, 1L << 6, &mouse_event, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0, &close_window, &mlx);
	mlx_hook(mlx.mlx_map, 17, 0, &close_window, &mlx);
	map_wallimg(&mlx);
	map_doorimg(&mlx);
	map_playerimg(&mlx);
	make_minimap(&mlx);
	draw_ray(&mlx);
	mlx_loop (mlx.mlx);
}
