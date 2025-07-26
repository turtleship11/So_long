/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:06:09 by jaeklee           #+#    #+#             */
/*   Updated: 2025/05/15 10:58:48 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_store(int fd, char *remember)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		read_bytes;

	while (!ft_strchr(remember, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buffer[read_bytes] = '\0';
		temp = ft_strjoin(remember, buffer);
		if (!temp)
		{
			free(remember);
			return (NULL);
		}
		free(remember);
		remember = temp;
	}
	return (remember);
}

static char	*extract_line(char *remember)
{
	char	*line;
	char	*new_line;
	int		len;

	if (!remember || *remember == '\0')
		return (NULL);
	new_line = ft_strchr(remember, '\n');
	if (new_line)
	{
		len = (new_line - remember) + 1;
		line = ft_substr(remember, 0, len);
	}
	else
		line = ft_strdup(remember);
	return (line);
}

static char	*find_newline(char *remember)
{
	char	*new_line;
	char	*temp;

	new_line = ft_strchr(remember, '\n');
	if (new_line && *(new_line + 1) != '\0')
	{
		temp = ft_strdup(new_line + 1);
		if (!temp)
		{	
			free(remember);
			return (NULL);
		}
		free(remember);
		return (temp);
	}
	free(remember);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*remember;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remember)
		remember = ft_strdup("");
	if (!remember)
		return (NULL);
	remember = read_and_store(fd, remember);
	if (!remember || *remember == '\0')
	{
		free(remember);
		remember = NULL;
		return (NULL);
	}
	line = extract_line(remember);
	if (!line)
	{
		free(remember);
		remember = NULL;
		return (NULL);
	}
	remember = find_newline(remember);
	return (line);
}
