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


int	main(int ac, char **av)
{
	t_game game;

	if (ac != 2)
	{
		write(2, "Input error, put only map\n", 26);
		return (-1);
	}
	map_check(av[1]);
	game = init_map(av[1]);
	copy_map_to_grid(&game);

	if (!validate_map(game) && !is_map_playable(&game))
	{
		write(2,"It's not playanle\n", 18);
		free_map(game.map);
		free_map(game.grid);
		return (-1);
	}

	game.mlx = mlx_init(game.width * 64, game.height * 64, "so_long", false);
	if (!game.mlx)
	{
		write(2, "Failed to initialize mlx\n", 25);
		free_map(game.map);
		free_map(game.grid);
		return (-1);
	}

	load_textures(&game, &textures);
	render_map(&game, &textures);
	// 이후 게임 실행
	// ...
	
	// 프로그램 종료 시 메모리 정리
	free_map(game.map);
	free_map(game.grid);
	return (0);
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

int	validate_map(t_game game)
{
	int		player = 0;
	int		exit = 0;
	int		item = 0;
	size_t	i = 0;

	while (i < game.height)
	{
		if ((int)ft_strlen(game.grid[i]) != (int)game.width)
		{
			write(2, "Error: Map is not rectangular\n", 30);
			return (0);
		}

		size_t j = 0;
		while (j < game.width)
		{
			char c = game.grid[i][j];

			if (i == 0 || i == game.height - 1 || j == 0 || j == game.width - 1)
			{
				if (c != '1')
				{
					write(2, "Error: Map borders must be walls\n", 33);
					return (0);
				}
			}

			if (c == 'P')
				player++;
			else if (c == 'E')
				exit++;
			else if (c == 'C')
				item++;
			else if (c != '0' && c != '1')
			{
				write(2, "Error: Invalid character in map\n", 32);
				return (0);
			}
			j++;
		}
		i++;
	}
	if (player != 1)
	{
		write(2, "Error: There must be exactly one player\n", 40);
		return (0);
	}
	if (exit < 1)
	{
		write(2, "Error: There must be at least one exit\n", 39);
		return (0);
	}
	if (item < 1)
	{
		write(2, "Error: There must be at least one collectible\n", 46);
		return (0);
	}
	return (1);
}



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