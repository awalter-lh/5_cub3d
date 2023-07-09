/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:25:09 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/07/08 20:22:38 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_info(t_parse_info *info)
{
	if (info->no)
		printf("no    : %s\n", info->no);
	if (info->so)
		printf("so    : %s\n", info->so);
	if (info->we)
		printf("we    : %s\n", info->we);
	if (info->ea)
		printf("ea    : %s\n", info->ea);
	if (info->floor)
		printf("floor : %s\n", info->floor);
	if (info->no)
		printf("sky   : %s\n", info->sky);
	printf("mapx  : %d\nmapy  : %d\n", info->mapx, info->mapy);
	printf("px  : %d\npy  : %d\npa  : %f\n", info->px, info->py, info->pa);
	if (info->map)
		for (int i = 0; info->map[i]; i++)
			printf("%2d %s\n", i, info->map[i]);
}

int	main(int ac, char *av[])
{
	t_parse_info	info;
	int				ret;

	if (ac != 2)
		return (0);
	info = parse_info_init();
	ret = check_file(av[1], &info);
	printf("check_file -> %d (\"%s\", info)\n", ret, av[1]);
	if (ret != -1)
	{
		print_info(&info);
		free_info(&info);
	}
	return (0);
}
