/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lee_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:53:07 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/07/09 04:38:09 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check(char **tab, int sz_y, int x, int y)
{
	int	sz_x;

	sz_x = (int)ft_strlen(tab[0]);
	if (y - 1 >= 0 && tab[y - 1][x] == 'F')
		return (1);
	if (y < sz_y - 1 && tab[y + 1][x] == 'F')
		return (1);
	if (x < sz_x - 1 && tab[y][x + 1] == 'F')
		return (1);
	if (x - 1 >= 0 && tab[y][x - 1] == 'F')
		return (1);
	if (y - 1 >= 0 && x < sz_x - 1 && tab[y - 1][x + 1] == 'F')
		return (1);
	if (y < sz_y - 1 && x < sz_x - 1 && tab[y + 1][x + 1] == 'F')
		return (1);
	if (y - 1 >= 0 && x - 1 >= 0 && tab[y -1][x - 1] == 'F')
		return (1);
	if (y < sz_y - 1 && x - 1 >= 0 && tab[y + 1][x - 1] == 'F')
		return (1);
	return (0);
}

int	modified_tab(char **tab, int sz_x, int sz_y, int *count)
{
	int	i;
	int	j;

	i = -1;
	while (tab && tab[++i])
	{
		j = -1;
		while (tab[i][++j])
		{
			if (check(tab, sz_y, j, i)
				&& (tab[i][j] == '0' || tab[i][j] == '2'))
			{
				if (i == 0 || j == 0 || i == sz_y - 1 || j == sz_x - 1)
					return (-1);
				tab[i][j] = 'F';
				(*count)++;
			}
		}
	}
	return (0);
}

void	change_pinfo(t_parse_info *info, int i, int j, char type)
{
	info->px = j * 64 + 32;
	info->py = i * 64 + 32;
	if (type == 'N')
		info->pa = PI3;
	if (type == 'S')
		info->pa = PI2;
	if (type == 'E')
		info->pa = 0;
	if (type == 'W')
		info->pa = PI;
}
