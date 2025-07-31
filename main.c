/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:13:29 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/31 17:57:26 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/so_long.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return_with_error("Input error, put only map\n");
	map_check(av[1]);
	game = init_map(av[1]);
	copy_map_to_grid(&game);
	if (!validate_map(game) || !is_map_playable(&game))
	{
		write(2, "It's not playable\n", 18);
		free_map(game.map);
		free_map(game.grid);
		exit(EXIT_FAILURE);
	}
	game.mlx = mlx_init(game.width * 64, game.height * 64, "so_long", false);
	if (!game.mlx)
	{
		write(2, "Failed to initialize mlx\n", 25);
		free_map(game.map);
		free_map(game.grid);
		return (-1);
	}
	main2(game);
	return (0);
}

void	main2(t_game game)
{
	t_textures	textures;

	load_textures(&textures);
	create_images(&game, &textures);
	render_map(&game);
	count_items(&game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_close_hook(game.mlx, close_hook, &game);
	mlx_loop(game.mlx);
	cleanup_images(&game);
	cleanup_textures(&textures);
	free_map(game.map);
	free_map(game.grid);
}
