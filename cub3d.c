/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awalter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:40:50 by awalter           #+#    #+#             */
/*   Updated: 2023/07/09 05:23:15 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx_map(t_parse_info *info, t_mlx *mlx)
{
	mlx->map.floor_color = extract_num(info->floor);
	mlx->map.sky_color = extract_num(info->sky);
	mlx->map.n_texture = xpm_parsing(info->no);
	mlx->map.s_texture = xpm_parsing(info->so);
	mlx->map.e_texture = xpm_parsing(info->ea);
	mlx->map.w_texture = xpm_parsing(info->we);
	mlx->map.mapx = info->mapx;
	mlx->map.mapy = info->mapy;
	mlx->map.map = info->map;
	mlx->player.px = info->px;
	mlx->player.py = info->py;
	mlx->player.pa = info->pa;
	mlx->player.pdx = cos(mlx->player.pa) * 5;
	mlx->player.pdy = sin(mlx->player.pa) * 5;
	free(info->floor);
	free(info->sky);
	free(info->no);
	free(info->so);
	free(info->ea);
	free(info->we);
}

void	init_map(char *str, t_mlx *mlx)
{
	t_parse_info	info;
	
	info = parse_info_init();
	if (-1 == check_file(str, &info))
	{
		mlx_destroy_display(mlx->mlx);
		free_buff(mlx);
		free(mlx->mlx);
		exit(0);
	}
	init_mlx_map(&info, mlx);
}

void	init_screen(char *str, t_mlx *mlx)
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
	init_map(str, mlx);
	mlx->mlx_win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "Cub3d");
	mlx->game_img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx = make_game_img(mlx);
	mlx->mlx_map = mlx_new_window(mlx->mlx,
			mlx->map.mapx * 16, mlx->map.mapy * 16, "MiniMap");
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac != 2)
		return (0);
	init_screen(av[1], &mlx);
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
	return (0);
}
