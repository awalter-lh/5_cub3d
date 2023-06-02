/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awalter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:40:38 by awalter           #+#    #+#             */
/*   Updated: 2023/06/02 09:40:39 by awalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_map
{
	int		sky_color;
	int		floor_color;
	int		wall_color;
	int		px;
	int		py;
	char	**map;
}	t_map;

typedef struct s_mlx {
	void	*mlx;
	void	*mlx_win;
	void	*bg;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		width;
	int		length;
	t_map	map;
}	t_mlx;



#endif
