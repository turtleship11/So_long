/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:13:29 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/29 14:42:16 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/so_long.h"


int	main(int ac, char **av)
{
	t_game game;
	t_textures textures;

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
	load_textures(&textures);
	create_images(&game, &textures);
	render_map(&game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_close_hook(game.mlx, close_hook, &game);
	mlx_loop(game.mlx);
	
	cleanup_images(&game);
	cleanup_textures(&textures);
	free_map(game.map);
	free_map(game.grid);
	return (0);
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
