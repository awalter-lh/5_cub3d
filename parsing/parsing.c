/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:16:27 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/07/06 15:47:28 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_file(char *str, t_parse_info *info)
{
	int	ret;
	int	fd;

	ret = 1;
	(void)info;
	if (!str)
		return (0);
	if (!check_ext(str, ".cub"))
		return (put_error("Error: wrong file extension", 1));
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (put_error(str, 2));
	if (-1 == extract_inf(fd, info, str))
		ret = -1;
	close(fd);
	return (ret);
}

int	extract_inf(int fd, t_parse_info *info, char *name)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
	}
	return (0);
}
