/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_map2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:50:31 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/31 12:52:02 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*read_map_str(const char *filename)
{
	int		fd;
	char	*map_str;

	fd = open(filename, O_RDONLY);
	if (fd == -1 || errno == EISDIR)
	{
		write(2, "Invalid map file\n", 17);
		exit(EXIT_FAILURE);
	}
	map_str = read_lines_into_str(fd);
	close(fd);
	return (map_str);
}

char	*read_lines_into_str(int fd)
{
	char	*line;
	char	*temp;
	char	*map_str;

	map_str = ft_strdup("");
	if (!map_str)
		exit_with_error("strdup error\n", fd);
	line = get_next_line(fd);
	while (line)
	{
		temp = map_str;
		map_str = ft_strjoin(map_str, line);
		free(temp);
		free(line);
		if (!map_str)
			exit_with_error("ft_strjoin error\n", fd);
		line = get_next_line(fd);
	}
	return (map_str);
}

void	exit_with_error(const char *msg, int fd)
{
	write(2, msg, ft_strlen(msg));
	close(fd);
	exit(EXIT_FAILURE);
}
