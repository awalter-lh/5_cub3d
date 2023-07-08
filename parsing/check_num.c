/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:53:07 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/07/08 11:52:00 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	value;

	i = 0;
	value = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (is_digit(nptr[i]))
	{
		if (value * sign > 2147483647)
			return (-1);
		else if (value * sign < -2147483648)
			return (0);
		value = value * 10 + nptr[i] - '0';
		i++;
	}
	return (value * sign);
}

int	check_num(char *str, int *act_pos)
{
	int		i;
	int		pos;
	char	num[4];

	i = -1;
	if (!str)
		return (-1);
	pos = *act_pos;
	while (str[++i + pos] && is_digit(str[i + pos]) && i < 3)
		num[i] = str[i + pos];
	if (i == 0 || (i == 3 && is_digit(str[i + pos])))
		return (-1);
	num[i] = 0;
	if (ft_atoi(num) > 255)
		return (-1);
	*act_pos = pos + i;
	return (0);
}

int	check_color_validity(char *str)
{
	int	pos;

	pos = 0;
	if (-1 == check_num(str, &pos))
		return (-1);
	if (!(str[pos] && str[pos] == ','))
		return (-1);
	pos++;
	if (-1 == check_num(str, &pos))
		return (-1);
	if (!(str[pos] && str[pos] == ','))
		return (-1);
	pos++;
	if (-1 == check_num(str, &pos))
		return (-1);
	return (0);
}

int	give_num(char *str, int *act_pos, int *res, int power)
{
	int		i;
	int		pos;
	char	num[4];

	i = -1;
	if (!str)
		return (-1);
	pos = *act_pos;
	while (str[++i + pos] && is_digit(str[i + pos]) && i < 3)
		num[i] = str[i + pos];
	num[i] = 0;
	*res += ft_atoi(num) * power;
	*act_pos = pos + i;
	return (0);
}

int	extract_num(char *str)
{
	int	pos;
	int	res;

	pos = 0;
	res = 0;
	give_num(str, &pos, &res, 65536);
	pos++;
	give_num(str, &pos, &res, 256);
	pos++;
	give_num(str, &pos, &res, 1);
	return (res);
}
