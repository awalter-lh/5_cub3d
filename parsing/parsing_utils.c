/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:01:53 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/07/08 09:42:45 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_tab(char **tab)
{
	int	i;
	
	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

int	empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_white_space(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	check_ext(char *name, char *ext)
{
	int	len_name;
	int	len_ext;

	len_name = ft_strlen(name);
	len_ext = ft_strlen(ext);
	if (len_name < len_ext)
		return (0);
	while (len_ext && name[len_name-- - 1] == ext[len_ext - 1])
		len_ext--;
	if (len_ext)
		return (0);
	return (1);
}

char	*remove_end(char *str)
{
	int		i;
	int		len;
	char	*ret;

	i = -1;
	len = 0;
	while (str[len])
		len++;
	if (str[len - 1] != '\n')
		return (str);
	ret = malloc(sizeof(char) * len);
	if (!ret)
		return (NULL);
	while (++i < len - 1)
		ret[i] = str[i];
	ret[i] = 0;
	free(str);
	return (ret);
}

void	free_info(t_parse_info *info)
{
	if (info->map)
		free_tab(info->map);
	if (info->no)
		free(info->no);
	if (info->so)
		free(info->so);
	if (info->we)
		free(info->we);
	if (info->ea)
		free(info->ea);
	if (info->floor)
		free(info->floor);
	if (info->sky)
		free(info->sky);
}

int	all_completed(t_parse_info *info)
{
	if (!info)
		return (1);
	if (!info->no || !info->so || !info->we || !info->ea
		|| !info->floor || !info->sky)
		return (0);
	return (1);
}
