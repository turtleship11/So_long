/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:13:29 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/26 18:00:29 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/so_long.h"


int		main(int ac, char **av)
{
	if (ac != 2)
	{
		write(2, "Input error, put only map\n", 26);
		return (-1);
	}
	map_check(av[1]);
	
}

int get_map_height(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
	{
		write(2, "Failed to open file\n", 20);		
		return (0);
	}
	int height = 0;
    char *line;
    while ((line = get_next_line(fd)))
    {
        height++;
        free(line);
    }
    close(fd);
    return (height);
}

t_game	init_map(char *av)
{
	t_game	game;

	read_map(&game, av);
	if (!game.map)
	{
		write(2, "Map reading failed\n", 20);
		exit(-1);	
	}
	return (game);
}

int		map_check(char *av)
{
	int	len;
	char *format;
	
	format = ".ber";
	len = 0;
	len = ft_strlen(av);
	if (len <= 4)
	{
		write(2,"file name error\n",16);
		exit(-1);
	}
	if (ft_strncmp(&av[len - 4], format, 4) != 0)
	{
		write(2,"file name error\n",16);
		exit(-1);		
	}
	return (1);
}


char	*read_map_str(const char *filename)
{
	int		fd;
	char	*line;
	char	*temp;
	char	*map_str;

	fd = open(filename, O_RDONLY);
	if (fd == -1 || errno == EISDIR)
	{
		write(2, "Invalid map file\n", 17);
		exit(EXIT_FAILURE);
	}
	map_str = ft_strdup("");
	if (!map_str)
	{
		write(2, "strdup error\n", 13);
		close(fd);
		exit(EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)))
	{
		temp = map_str;
		map_str = ft_strjoin(map_str, line);
		free(temp);
		free(line);
	}
	close(fd);
	return (map_str);
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
		write(2, "Map format invalid\n", 20);
		exit(EXIT_FAILURE);
	}
	game->width = ft_strlen(game->map[0]);
}
void copy_map_to_grid(t_game *game)
{
    size_t i = 0;

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


// char	**read_map(char *av)
// {
// 	int	fd;
// 	char **map;
// 	char *line;
// 	char *map_str;
// 	char *temp;
// 	int height;
// 	int i;

// 	fd = open(av, O_RDONLY);
// 	if (fd == -1 || errno == EISDIR)
// 	{
// 		write(2, "Invalid map file\n", 17);
// 		return (NULL);
// 	}
//     height = get_map_height(filename);
//     if (height <= 0) 
// 	{
// 		write(2, "Map is empty\n", 13);
// 		return (NULL);		
// 	}
// 	map->height = height;
// 	map_str = ft_strdup("");
// 	if (!map_str)
// 	{
// 		write(2,"strdup error\n", 13);
// 		exit(-1);
// 	}
// 	while ((line = get_next_line(fd)))
// 	{
// 		temp = map_str;
// 		map_str = ft_strjoin(map_str, line);
// 		free(temp);
// 		free(line);
// 	}
// 	close(fd);
// 	map = ft_split(map_str, '\n');
// 	free(map_str);
// 	if (height > 0)
// 		map->width = strlen(map[0]);
// 	else
// 		map->height = 0; 
// 	return (map);
// }

// void	read_map(t_game *game, char *filename)
// {
// 	int		fd;
// 	char	*line;
// 	char	*temp;
// 	char	*map_str;

// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1 || errno == EISDIR)
// 	{
// 		write(2, "Invalid map file\n", 17);
// 		exit(EXIT_FAILURE);
// 	}
// 	game->height = get_map_height(filename);
// 	if (game->height <= 0)
// 	{
// 		write(2, "Map is empty\n", 13);
// 		close(fd);
// 		exit(EXIT_FAILURE);
// 	}
// 	map_str = ft_strdup("");
// 	if (!map_str)
// 	{
// 		write(2, "strdup error\n", 13);
// 		close(fd);
// 		exit(EXIT_FAILURE);
// 	}
// 	while ((line = get_next_line(fd)))
// 	{
// 		temp = map_str;
// 		map_str = ft_strjoin(map_str, line);
// 		free(temp);
// 		free(line);
// 	}
// 	close(fd);

// 	game->map = ft_split(map_str, '\n');
// 	free(map_str);

// 	if (!game->map || !game->map[0])
// 	{
// 		write(2, "Map format invalid\n", 20);
// 		exit(EXIT_FAILURE);
// 	}
// 	game->width = ft_strlen(game->map[0]);
// }