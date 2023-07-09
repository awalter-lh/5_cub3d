/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:57:09 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/07/09 04:39:02 by nbeaufil         ###   ########.fr       */
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
# define PI 3.1415926535
# define PI2 PI/2
# define PI3 3*PI/2

/* ========== struct ========== */

typedef struct s_parse_info
{
	int		mapx;
	int		mapy;
	int		px;
	int		py;
	float	pa;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*floor;
	char	*sky;
}	t_parse_info;

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
int				is_digit(char c);
int				is_white_space(char c);
int				put_error(char *str, int code);
int				comp(const char *s1, const char *s2);

/* ========== parsing ========== */
int				check_file(char *str, t_parse_info *info);
int				file_extractor(int fd, t_parse_info *info, char *name);
int				extract_inf(t_parse_info *info,
					char *line, char *name, int idx);

/* ======= parsing_utils ======= */
int				empty_line(char *str);
int				check_ext(char *name, char *ext);
char			*remove_end(char *str);
void			free_info(t_parse_info *info);
int				all_completed(t_parse_info *info);

/* ======== parsing_ext ========= */
int				is_in(int type, t_parse_info *info);
void			ft_putnbr_fd(int n, int fd);
int				check_info_validity(int type, char *path);

/* ========= check_num ========= */
int				ft_atoi(const char *nptr);
int				check_num(char *str, int *act_pos);
int				check_color_validity(char *str);
int				give_num(char *str, int *act_pos, int *res, int power);
int				extract_num(char *str);

/* ======== extract_inf ======== */
int				type_error(int type, char *name, int idx);
void			assign_type(t_parse_info *info, int type, char *path);
int				type_finder(char *type);
int				extract_type(int *pos, char *str);
char			*extract_path(char *path, int pos);

/* ======== extract_map ======== */
char			**tdtab_push(char **tab, char *to_add);
char			**find_map(int fd);
void			find_greater(t_parse_info *info, char **tab);
int				extract_map(int fd, t_parse_info *info);

/* ====== extract_map_ext ====== */
void			find_pos(t_parse_info *info);
int				check_map(char **tab, int sz_x, int sz_y);
int				check_tab_char(char **tab, int pos);
char			**duplicate_tab(char **tab);

/* ========== lee_algo ========= */
int				check(char **tab, int size, int x, int y);
int				modified_tab(char **tab, int sz_x, int sz_y, int *count);
void			change_pinfo(t_parse_info *info, int i, int j, char type);
char			**free_tab(char **tab);

#endif
