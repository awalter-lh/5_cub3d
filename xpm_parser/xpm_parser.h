/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awalter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:14:56 by awalter           #+#    #+#             */
/*   Updated: 2023/06/17 13:14:57 by awalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XPM_PARSER_H
# define XPM_PARSER_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "./get_next_line/get_next_line.h"

typedef struct s_xmp
{
	int		nb_char;
	int		nb_color;
	int		nb_colomn;
	int		nb_row;
	char	**str_tab;
	int		*values;
	int		**mat;
}	t_xpm;

char	**ft_split(char *str, char c);
int		ft_atoi(char *nptr);
int		fill_mat(int fd, t_xpm *xpm);
t_xpm	*xpm_parsing(char *file);
size_t	ft_strlcpy(char *dst, char *src, size_t size);

#endif
