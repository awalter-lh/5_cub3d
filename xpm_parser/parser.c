/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awalter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:13:39 by awalter           #+#    #+#             */
/*   Updated: 2023/06/17 13:13:41 by awalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xpm_parser.h"

char	*get_str(char *buff, t_xpm *xpm, int index)
{
	int	i;
	int	j;

	i = -1;
	xpm->str_tab[index] = malloc(sizeof(char) * (xpm->nb_char + 1));
	if (!xpm->str_tab[index])
		return (NULL);
	i = 0;
	j = 0;
	while (++i <= xpm->nb_char)
	{
		xpm->str_tab[index][j] = buff[i];
		j++;
	}
	xpm->str_tab[index][j] = '\0';
	return (buff);
}

int	get_color(char *buff)
{
	int		color;
	int		i;
	int		y;

	i = 0;
	while (buff[i])
		i++;
	i -= 9;
	color = 0;
	y = 5;
	while (buff[i] != '"')
	{
		if ('0' <= buff[i] && buff[i] <= '9')
			color = color + (buff[i] - '0') + pow(16, y);
		else if ('A' <= buff[i] && buff[i] <= 'F')
			color = color + (buff[i] - 'A' + 10) + pow(16, y);
		y--;
		i++;
	}
	return (color);
}

int	fill_values(int fd, t_xpm *xpm)
{
	int		i;
	char	*buff;

	i = -1;
	xpm->str_tab = malloc(sizeof(char *) * (xpm->nb_color + 1));
	xpm->values = malloc(sizeof(int) * xpm->nb_color);
	if (!xpm->str_tab || !xpm->values)
		return (1);
	while (++i < xpm->nb_color)
	{
		buff = get_next_line(fd);
		if (!get_str(buff, xpm, i))
			return (1);
		xpm->values[i] = get_color(buff);
		free(buff);
	}
	return (0);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

t_xpm	*xpm_parsing(char *file)
{
	int		fd;
	t_xpm	*xpm;
	char	**tab;

	xpm = malloc(sizeof(t_xpm));
	fd = open(file, O_RDONLY);
	if (!xpm || fd == -1)
		return (NULL);
	free(get_next_line(fd));
	free(get_next_line(fd));
	tab = ft_split(get_next_line(fd), ' ');
	if (!tab)
		return (NULL);
	xpm->nb_colomn = ft_atoi(tab[0] + 1);
	xpm->nb_row = ft_atoi(tab[1]);
	xpm->nb_color = ft_atoi(tab[2]);
	xpm->nb_char = ft_atoi(tab[3]);
	free_tab(tab);
	if (fill_values(fd, xpm) || fill_mat(fd, xpm))
		return (NULL);
	close (fd);
	return (xpm);
}
