/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:53:07 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/07/08 23:19:08 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**tdtab_push(char **tab, char *to_add)
{
	int		len;
	char	**ret;

	len = 0;
	while (tab && tab[len])
		len++;
	ret = malloc(sizeof(char *) * (len + 2));
	if (!ret)
		return (NULL);
	len = 0;
	while (tab && tab[len])
	{
		ret[len] = tab[len];
		if (!ret[len++])
			return (free_tab(ret));
	}
	ret[len] = ft_strdup(to_add);
	if (!ret[len++])
		return (free_tab(ret));
	ret[len] = NULL;
	free(tab);
	return (ret);
}

char	**find_map(int fd)
{
	char	*line;
	char	**ret;

	ret = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		if (!empty_line(line))
			break ;
		free(line);
	}
	while (line && !empty_line(line))
	{
		line = remove_end(line);
		ret = tdtab_push(ret, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (ret);
}

void	find_greater(t_parse_info *info, char **tab)
{
	int	size;

	while (tab && tab[info->mapy])
	{
		size = ft_strlen(tab[info->mapy]);
		if (size > info->mapx)
			info->mapx = size;
		info->mapy++;
	}
}

void	new_map(t_parse_info *info, char **tab)
{
	int	i;
	int	j;

	i = -1;
	info->map = malloc(sizeof(char *) * (info->mapy + 1));
	if (!info->map)
		return ;
	while (++i < info->mapy)
	{
		j = -1;
		info->map[i] = malloc(sizeof(char) * (info->mapx + 1));
		while (++j < info->mapx)
		{
			if (j >= (int)ft_strlen(tab[i]) || (tab[i] && tab[i][j] == ' '))
				info->map[i][j] = '0';
			else
				info->map[i][j] = tab[i][j];
		}
		info->map[i][j] = 0;
	}
	info->map[i] = NULL;
}

int	extract_map(int fd, t_parse_info *info)
{
	char	**tab;

	tab = find_map(fd);
	if (!tab)
		return (put_error("error: no map", 1));
	find_greater(info, tab);
	new_map(info, tab);
	free_tab(tab);
	tab = duplicate_tab(info->map);
	if (-1 == check_map(tab, info->mapx, info->mapy))
	{
		free_tab(tab);
		return (put_error("error: problem(s) with map", 1));
	}
	free_tab(tab);
	find_pos(info);
	return (0);
}
