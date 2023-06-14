/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:16:27 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/06/14 11:00:22 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_file(char *str, t_parse_info *info)
{
	int	fd;

	if (!str)
		return (0);
	if (!check_ext(str, ".cub"))
		return (put_error("Error: wrong file extension", 1));
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (put_error(str, 2));
	if (-1 == extract_inf(fd, info, name))
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	read_file(int fd, t_parse_info *info, char *name)
{
	int				status;
	char			*line;
	t_parse_error	error;

	error = init_error();
	line = get_next_line(fd);
	while (line)
	{
		status = 0;
		line = remove_end(line);
		if (!empty_line(line))
		{
			if (-1 == extract_info(line, info, &error)) // enregistre la ligne dans info ou renvoie -1 et remplit error
			{
				extraction_error(error, name); // to_do: fonction qui ecrit l'erreur
				free(line);
				return (-1);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	extract_info(char *line, t_parse_inf *info, t_parse_error *error)
{
	int		i;
	int		j;
	char	*id;
	char	*value;

	i = 0;
	while (line[i] && is_white_space(line[i]))
		i++;
	j = i;
	while (line[j] && !is_white_space(line[j]))
		j++;
	id = strtronq(line, i, j);
	if (!id)
		return (put_error("error: heap allocation does not works", 1));
	if (-1 == check_id(id, info, error)) // regarde si id est correct et si il n'a pas deja ete rencontre
		return (-1);
	while (line[j] && is_white_space(line[j]))
		j++;
	value = strtronq(line, j, -1);
	if (!value)
	{
		free(id);
		return (put_error("error: heap allocation does not works", 1));
	}
	if (-1 == store_line(id, value, info, error)) // conserve la 
		return (-1);
	return (0);
}
