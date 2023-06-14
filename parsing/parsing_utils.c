/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:01:53 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/06/13 13:59:47 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
