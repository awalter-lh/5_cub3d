/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awalter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:49:53 by awalter           #+#    #+#             */
/*   Updated: 2023/06/22 13:49:54 by awalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_xpm_struct(t_xpm *xpm)
{
	int	i;

	i = 0;
	free(xpm->values);
	while (xpm->str_tab[i])
	{
		free(xpm->str_tab[i]);
		i++;
	}
	free(xpm->str_tab[i]);
	free(xpm->str_tab);
	i = 0;
	while (i < xpm->nb_row)
	{
		free(xpm->mat[i]);
		i++;
	}
	free(xpm->mat);
	free(xpm);
}

void	free_map(t_map map)
{
	int	i;

	i = 0;
	while (i <= map.mapy)
	{
		free(map.map[i]);
		i++;
	}
	free(map.map);
}

void	free_buff(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < mlx->height)
	{
		free(mlx->buff[i]);
		free(mlx->t_buff[i]);
		i++;
	}
	free(mlx->buff);
	free(mlx->t_buff);
}

int	close_window(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->game_img);
	mlx_destroy_image(mlx->mlx, mlx->pimg);
	mlx_destroy_image(mlx->mlx, mlx->wimg);
	mlx_destroy_image(mlx->mlx, mlx->dimg);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	mlx_destroy_window(mlx->mlx, mlx->mlx_map);
	mlx_destroy_display(mlx->mlx);
	free_xpm_struct(mlx->map.n_texture);
	free_xpm_struct(mlx->map.s_texture);
	free_xpm_struct(mlx->map.e_texture);
	free_xpm_struct(mlx->map.w_texture);
	free_map(mlx->map);
	free_buff(mlx);
	free(mlx->mlx);
	exit(0);
}
