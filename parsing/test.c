/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:25:09 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/06/13 14:25:49 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*int	main(int ac, char *av[])
{
	int		fd;
	char	*line;

	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (-1);
	}
	printf("line              == \"%s\"\n\n", line);
	line = remove_end(line);
	printf("line no end       == \"%s\"\n\n", line);
	line = remove_end(line);
	printf("line no end again == \"%s\"\n\n", line);
	free(line);
	close(fd);
	return (0);
}
*/

int	main(int ac, char *av[])
{
	if (ac != 2)
		return (0);
	printf("check_file -> %d (\"%s\", NULL)\n", check_file(av[1], NULL), av[1]);
	return (0);
}
