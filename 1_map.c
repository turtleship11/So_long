/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:47:57 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/31 14:09:46 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_check(char *av)
{
	int		len;
	char	*format;

	format = ".ber";
	len = 0;
	len = ft_strlen(av);
	if (len <= 4)
	{
		write(2, "file name error\n", 16);
		exit(-1);
	}
	if (ft_strncmp(&av[len - 4], format, 4) != 0)
	{
		write(2, "file name error\n", 16);
		exit(-1);
	}
	return (1);
}

t_game	init_map(char *av)
{
	t_game	game;

	read_map(&game, av);
	game.move_count = 0;
	if (!game.map)
	{
		write(2, "Map reading failed\n", 20);
		exit(-1);
	}
	return (game);
}

void	read_map(t_game *game, char *filename)
{
	char	*map_str;

	game->height = get_map_height(filename);
	if (game->height <= 0)
	{
		write(2, "Map is empty\n", 13);
		exit(EXIT_FAILURE);
	}
	map_str = read_map_str(filename);
	game->map = ft_split(map_str, '\n');
	free(map_str);
	if (!game->map || !game->map[0])
	{
		if (game->map)
			free_map(game->map);
		write(2, "Map format invalid\n", 20);
		exit(EXIT_FAILURE);
	}
	game->width = ft_strlen(game->map[0]);
}

int	get_map_height(const char *filename)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Failed to open file\n", 20);
		return (0);
	}
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

void	copy_map_to_grid(t_game *game)
{
	size_t	i;

	i = 0;
	game->grid = malloc(sizeof(char *) * (game->height + 1));
	if (!game->grid)
		exit(EXIT_FAILURE);
	while (i < game->height)
	{
		game->grid[i] = ft_strdup(game->map[i]);
		if (!game->grid[i])
		{
			while (i > 0)
				free(game->grid[--i]);
			free(game->grid);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	game->grid[i] = NULL;
}
