/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:57:09 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/06/13 15:25:03 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/* ========== error ========== */
# define ERROR1 "invalid ID"
# define ERROR2 "multiple ID definition"

/* ========== struct ========== */

typedef struct s_parse_info
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*floor;
	char	*sky;
}	t_parse_info;

typedef struct s_parse_error
{
	int		type;
	int		word;
	int		line_idx;
	char	*line;
}	t_parse_error;

/* ========= utils_gnl ========= */
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strchr(const char *s, int c);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *s);

/* =========== proto =========== */
char			*get_next_line(int fd);

/* =========== utils =========== */
t_parse_info	parse_info_init(void);
t_parse_error	init_error(void);
int				is_white_space(char c);
int				put_error(char *str, int code);

/* ========== parsing ========== */
int				check_file(char *str, t_parse_info *info);

/* ======= parsing_utils ======= */
int				empty_line(char *str);
int				check_ext(char *name, char *ext);
char			*remove_end(char *str);

#endif
