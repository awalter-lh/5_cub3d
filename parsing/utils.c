/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:58:04 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/06/14 11:00:28 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_white_space(char c)
{
	return ((c >= 7 && c <= 13) || c == 32);
}

int	put_error(char *str, int code)
{
	int	i;

	i = -1;
	if (code == 1)
	{
		while (str[++i])
			write(2, &str[i], 1);
		write(2, "\n", 1);
	}
	else if (code == 2)
		perror(str);
	return (-1);
}

t_parse_info	parse_info_init(void)
{
	t_parse_info	ret;

	ret.map = NULL;
	ret.no = NULL;
	ret.so = NULL;
	ret.we = NULL;
	ret.ea = NULL;
	ret.floor = NULL;
	ret.sky = NULL;
	return (ret);
}

t_parse_error	init_error(void)
{
	t_parse_error	ret;

	ret.word = -1;
	ret.line_idx = -1;
	ret.line = NULL;
	return (ret);
}
