/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_ext.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:53:07 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/07/08 23:26:03 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	**duplicate_tab(char **tab)
{
	int		i;
	char	**ret;

	i = -1;
	ret = NULL;
	while (tab && tab[++i])
	{
		ret = tdtab_push(ret, tab[i]);
		if (!ret)
			return (NULL);
	}
	return (ret);
}

int	check_tab_char(char **tab, int pos)
{
	int	i;
	int	j;

	i = -1;
	while (tab && tab[++i])
	{
		j = -1;
		while (tab[i][++j])
		{
			if (tab[i][j] == 'N' || tab[i][j] == 'S'
					|| tab[i][j] == 'E' || tab[i][j] == 'W')
			{
				tab[i][j] = 'F';
				pos++;
			}
			else if (tab[i][j] >= '0' && tab[i][j] <= '2')
				continue ;
			else
				return (-1);
		}
	}
	if (pos != 1)
		return (-1);
	return (0);
}

int	check_map(char **tab, int sz_x, int sz_y)
{
	int	ret;
	int	count;

	if (-1 == check_tab_char(tab, 0))
		return (-1);
	while (1)
	{
		count = 0;
		ret = modified_tab(tab, sz_x, sz_y, &count);
		if (ret == -1 || !count)
			break ;
	}
	return (ret);
}

void	find_pos(t_parse_info *info)
{
	int		i;
	int		j;
	char	type;

	i = -1;
	while (info && info->map && info->map[++i])
	{
		j = -1;
		while (info->map[i][++j])
		{
			type = info->map[i][j];
			if (type != '0' && type != '1' && type != '2')
			{
				change_pinfo(info, i, j, type);
				return ;
			}
		}
	}
}
