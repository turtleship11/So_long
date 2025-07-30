/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:29:38 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/30 19:17:46 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_textures(t_textures *textures)
{
	textures->wall = mlx_load_png("assets/wall.png");
	textures->floor = mlx_load_png("assets/floor.png");
	textures->player = mlx_load_png("assets/player.png");
	textures->item = mlx_load_png("assets/item.png");
	textures->exit_g = mlx_load_png("assets/exit.png");
	if (!textures->wall || !textures->floor || !textures->player
		|| !textures->item || !textures->exit_g)
	{
		if (textures->wall)
			mlx_delete_texture(textures->wall);
		if (textures->floor)
			mlx_delete_texture(textures->floor);
		if (textures->player)
			mlx_delete_texture(textures->player);
		if (textures->item)
			mlx_delete_texture(textures->item);
		if (textures->exit_g)
			mlx_delete_texture(textures->exit_g);
		write(2, "Failed to load textures\n", 24);
		exit(EXIT_FAILURE);
	}
}

void	draw_tile(t_game *game, mlx_image_t *img, int x, int y)
{
	mlx_image_to_window(game->mlx, img, x * 64, y * 64);
}

void	create_images(t_game *game, t_textures *textures)
{
	game->wall_img = mlx_texture_to_image(game->mlx, textures->wall);
	game->floor_img = mlx_texture_to_image(game->mlx, textures->floor);
	game->player_img = mlx_texture_to_image(game->mlx, textures->player);
	game->item_img = mlx_texture_to_image(game->mlx, textures->item);
	game->exit_img = mlx_texture_to_image(game->mlx, textures->exit_g);
	if (!game->wall_img || !game->floor_img || !game->player_img
		|| !game->item_img || !game->exit_img)
	{
		write(2, "Failed to create images\n", 25);
		exit(EXIT_FAILURE);
	}
}

void	render_map(t_game *game)
{
	size_t	x;
	size_t	y;
	char	tile;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			tile = game->grid[y][x];
			if (tile == '0' || tile != '1')
				draw_tile(game, game->floor_img, x, y);
			else if (tile == '1')
				draw_tile(game, game->wall_img, x, y);

			if (tile == 'P')
				draw_tile(game, game->player_img, x, y);
			else if (tile == 'C')
				draw_tile(game, game->item_img, x, y);
			else if (tile == 'E')
				draw_tile(game, game->exit_img, x, y);

			x++;
		}
		y++;
	}
}

void	cleanup_images(t_game *game)
{
	if (game->wall_img)
		mlx_delete_image(game->mlx, game->wall_img);
	if (game->floor_img)
		mlx_delete_image(game->mlx, game->floor_img);
	if (game->player_img)
		mlx_delete_image(game->mlx, game->player_img);
	if (game->item_img)
		mlx_delete_image(game->mlx, game->item_img);
	if (game->exit_img)
		mlx_delete_image(game->mlx, game->exit_img);
}

void	cleanup_textures(t_textures *textures)
{
	if (textures->wall)
		mlx_delete_texture(textures->wall);
	if (textures->floor)
		mlx_delete_texture(textures->floor);
	if (textures->player)
		mlx_delete_texture(textures->player);
	if (textures->item)
		mlx_delete_texture(textures->item);
	if (textures->exit_g)
		mlx_delete_texture(textures->exit_g);
}
