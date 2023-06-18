/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:28:06 by nbeaufil          #+#    #+#             */
/*   Updated: 2023/06/12 16:17:14 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*ret;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ret = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!ret)
		return (NULL);
	while (++i < len1)
		ret[i] = s1[i];
	i = -1;
	while (++i < len2)
		ret[len1 + i] = s2[i];
	ret[len1 + len2] = 0;
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	if (!c && s)
		return ((char *)&s[ft_strlen(s)]);
	while (s[++i])
		if (s[i] == c)
			return ((char *)&s[i]);
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*ptr;
	void	*ret;

	i = 0;
	if (nmemb == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	ret = malloc(size * nmemb);
	if (!ret)
		return (NULL);
	ptr = ret;
	while (i < size * nmemb)
		ptr[i++] = 0;
	return (ret);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*ret;

	i = -1;
	len = 0;
	while (s[len])
		len++;
	if (!len)
		return (NULL);
	ret = malloc(sizeof(char) * len + 1);
	if (!ret)
		return (NULL);
	while (++i < len)
		ret[i] = s[i];
	ret[i] = 0;
	return (ret);
}
