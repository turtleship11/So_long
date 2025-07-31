/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:58:28 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/31 18:36:23 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	return_with_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void	win_game(t_game *game)
{
	write(1, "You win!\n", 9);
	mlx_terminate(game->mlx);
	exit(0);
}
