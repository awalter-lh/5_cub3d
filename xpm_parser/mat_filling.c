/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_filling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awalter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:33:54 by awalter           #+#    #+#             */
/*   Updated: 2023/06/18 11:33:56 by awalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xpm_parser.h"

int	comp(char *str, char *buff)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (buff[i] != str[i])
			return (0);
		i++;
	}
	return (1);
}

int	find_value(char *buff, t_xpm *xpm)
{
	int	i;

	i = 0;
	while (xpm->str_tab[i])
	{
		if (comp(xpm->str_tab[i], buff))
			return (xpm->values[i]);
		i++;
	}
	return (-1);
}

void	mat_loop(int fd, t_xpm *xpm)
{
	int		i;
	int		x;
	int		y;
	char	*buff;

	y = -1;
	while (++y < xpm->nb_row)
	{
		i = 1;
		x = 0;
		buff = get_next_line(fd);
		while (buff[i] != '"')
		{
			xpm->mat[y][x] = find_value(&buff[i], xpm);
			x++;
			i += xpm->nb_char;
		}
		free(buff);
	}
}

int	fill_mat(int fd, t_xpm *xpm)
{
	int	i;

	xpm->mat = malloc(sizeof(int *) * xpm->nb_row);
	if (!xpm->mat)
		return (1);
	i = -1;
	while (++i < xpm->nb_row)
	{
		xpm->mat[i] = malloc(sizeof(int) * (xpm->nb_colomn));
		if (!xpm->mat[i])
			return (1);
	}
	mat_loop(fd, xpm);
	return (0);
}
