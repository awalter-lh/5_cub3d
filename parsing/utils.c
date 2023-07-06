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

int	comp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	while ((t1[i] && t2[i]) && (t1[i] == t2[i]))
		i++;
	return (t1[i] - t2[i]);
}
