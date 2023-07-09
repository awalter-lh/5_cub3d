/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:02:47 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/06/12 20:44:06 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

/* ========== utils ========== */
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);

/* =========== gnl =========== */
char	*get_next_line(int fd);
char	*rd_endl(int fd, char *ret);
char	*get_line(char *buff);
char	*line_remainder(char *buff);
char	*ft_strcat_mall(char *buff1, char *buff2);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef FD_LIMIT
#  define FD_LIMIT 256
# endif

#endif
