/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:16:27 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/07/08 20:32:41 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_file(char *str, t_parse_info *info)
{
	int	ret;
	int	fd;

	ret = 1;
	if (!str)
		return (0);
	if (!check_ext(str, ".cub"))
		return (put_error("Error: wrong file extension", 1));
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (put_error(str, 2));
	if (-1 == file_extractor(fd, info, str))
		ret = -1;
	close(fd);
	if (ret == -1)
		free_info(info);
	return (ret);
}

int	file_extractor(int fd, t_parse_info *info, char *name)
{
	char	*line;
	int		idx;
	int		ret;

	idx = 0;
	while (1)
	{
		ret = 0;
		line = get_next_line(fd);
		idx++;
		if (!line || all_completed(info))
			break ;
		if (!empty_line(line))
			ret = extract_inf(info, line, name, idx);
		free(line);
		if (ret == -1)
			return (-1);
	}
	free(line);
	if (!all_completed(info))
		return (-1);
	if (-1 == extract_map(fd, info))
		return (-1);
	return (0);
}

int	extract_inf(t_parse_info *info, char *line, char *name, int idx)
{
	int		pos;
	int		type;
	char	*path;

	type = extract_type(&pos, line);
	if (type < 0)
		return (type_error(type, name, idx));
	else if (is_in(type, info))
		return (type_error(-4, name, idx));
	path = extract_path(line, pos);
	if (!path)
		return (put_error("error: allocation failed\n", 1));
	if (-1 == check_info_validity(type, path))
	{
		free(path);
		return (-1);
	}
	assign_type(info, type, path);
	return (0);
}
