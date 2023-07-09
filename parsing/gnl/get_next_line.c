/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:04:43 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/06/12 20:43:45 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	save[FD_LIMIT][BUFFER_SIZE];
	char		*buff;
	char		*line;
	int			idx_buff;
	int			idx_save;

	idx_buff = 0;
	idx_save = 0;
	if (fd < 0 || fd > FD_LIMIT || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	buff = rd_endl(fd, ft_strdup(save[fd]));
	if (!buff)
		return (NULL);
	line = get_line(buff);
	while (buff[idx_buff] && buff[idx_buff] != '\n')
		idx_buff++;
	idx_buff++;
	if (idx_buff < (int)ft_strlen(buff))
		while (buff[idx_buff] && idx_save < BUFFER_SIZE)
			save[fd][idx_save++] = buff[idx_buff++];
	save[fd][idx_save] = 0;
	free(buff);
	return (line);
}

char	*rd_endl(int fd, char *ret)
{
	char	*buff;
	int		bytes;

	if (!ret)
		ret = ft_calloc(1, 1);
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes] = 0;
		ret = ft_strcat_mall(ret, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (ret);
}

char	*get_line(char *buff)
{
	int		i;
	char	*line;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), i + 2);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] && buff[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*ft_strcat_mall(char *buff1, char *buff2)
{
	char	*tmp;

	tmp = ft_strjoin(buff1, buff2);
	free(buff1);
	return (tmp);
}
