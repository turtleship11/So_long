/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:53:09 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/25 09:36:24 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map(char *filename, t_game *game)
{
	int  fd;
	char *line;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	game->hei = 0;
	game->wid = ft_strlen(line) - 1;
	game->str_line = ft_strdup_without_newline(line);
	free(line);
	while (line)
	{
		game->hei++;
		line = get_next_line(fd);
		if (line)
		{
			game->str_line = ft_strjoin_without_newline(game->str_line, line);
		}
	}
	close(fd);
	printf("%s\n", game->str_line);
	
}
