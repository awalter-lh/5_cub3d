/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_inf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:53:07 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/07/06 15:26:55 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// -1 empty line
// -2 no path
// -3 bad type
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
	if (!(str && str[i] && is_white_space(str[i])))
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
