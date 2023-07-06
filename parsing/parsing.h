/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:57:09 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/07/06 15:45:01 by nbeaufil         ###   ########.fr       */
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
# define ERROR3 "no path after ID"

/* ========== struct ========== */

typedef struct s_parse_info
{
	int		mapx;
	int		mapy;
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

/* ========= utils_gnl ========= */
int				type_finder(char *type);
int				extract_type(int *pos, char *str);
char			*extract_path(char *path, int pos);

/* =========== utils =========== */
t_parse_info	parse_info_init(void);
t_parse_error	init_error(void);
int				is_white_space(char c);
int				put_error(char *str, int code);
int				comp(const char *s1, const char *s2);

/* ========== parsing ========== */
int				check_file(char *str, t_parse_info *info);
int				file_extractor(int fd, t_parse_info *info, char *name);
int				extract_inf(t_parse_info *info, char *line, char *name);

/* ======= parsing_utils ======= */
int				empty_line(char *str);
int				check_ext(char *name, char *ext);
char			*remove_end(char *str);
void			free_info(t_parse_info *info);
int				all_completed(t_parse_info *info);

/* ======== extract_inf ======== */
int				type_error(int type, char *name);
void			assign_type(t_parse_info *info, int type, char *path);
int				type_finder(char *type);
int				extract_type(int *pos, char *str);
char			*extract_path(char *path, int pos);

#endif
