/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_inf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:53:07 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/07/08 20:25:29 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// -1 empty line
// -2 no path
// -3 bad type
// -4 already in
int	type_error(int type, char *name, int idx)
{
	put_error("error: ", 3);
	put_error(name, 3);
	put_error(" (", 3);
	ft_putnbr_fd(idx, 2);
	put_error("): ", 3);
	if (type == -2)
		put_error(ERROR3, 1);
	else if (type == -3)
		put_error(ERROR1, 1);
	else if (type == -4)
		put_error(ERROR2, 1);
	return (-1);
}

void	assign_type(t_parse_info *info, int type, char *path)
{
	if (type == 1)
		info->no = path;
	if (type == 2)
		info->so = path;
	if (type == 3)
		info->we = path;
	if (type == 4)
		info->ea = path;
	if (type == 5)
		info->floor = path;
	if (type == 6)
		info->sky = path;
}

int	type_finder(char *type)
{
	if (!comp(type, "NO"))
		return (1);
	if (!comp(type, "SO"))
		return (2);
	if (!comp(type, "WE"))
		return (3);
	if (!comp(type, "EA"))
		return (4);
	if (is_white_space(type[1]) && type[0] == 'F')
		return (5);
	if (is_white_space(type[1]) && type[0] == 'C')
		return (6);
	return (-3);
}

int	extract_type(int *pos, char *str)
{
	int		i;
	char	type[3];

	i = 0;
	while (str && str[i] && is_white_space(str[i]))
		i++;
	if (!(str && str[i] && str[i + 1]))
		return (-1);
	type[0] = str[i];
	type[1] = str[i + 1];
	type[2] = 0;
	i += 2;
	if (!(str && str[i]) && (is_white_space(str[i])
			&& !is_white_space(type[1])))
		return (-3);
	while (str && str[i] && is_white_space(str[i]))
		i++;
	if (str && !str[i])
		return (-2);
	(*pos) = i;
	return (type_finder(type));
}

char	*extract_path(char *path, int pos)
{
	int		i;
	int		len;
	char	*ret;

	len = 0;
	i = pos;
	if (!path)
		return (NULL);
	while (path[i++])
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < len && !is_white_space(path[i + pos]))
		ret[i] = path[i + pos];
	ret[i] = 0;
	return (ret);
}
