/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:06:09 by jaeklee           #+#    #+#             */
/*   Updated: 2025/05/14 18:32:22 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (c == '\0')
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = malloc(ft_strlen(src) + 1);
	if (!tmp)
		return (NULL);
	while (src[i] != '\0')
	{
		tmp[i] = src[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	char		*tmp;
	int			s1_len;
	int			s2_len;

	i = 0;
	j = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	tmp = malloc(s1_len + s2_len + 1);
	if (!tmp)
		return (NULL);
	while (s1[i] != '\0')
	{
		tmp[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		tmp[i + j] = s2[j];
		j++;
	}
	tmp[i + j] = '\0';
	return (tmp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*tmp;
	int		s_len;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (len > s_len - start)
		len = s_len - start;
	tmp = malloc(len + 1);
	if (!tmp)
		return (NULL);
	while (i < len)
	{
		tmp[i] = s[start + i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
