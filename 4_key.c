/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_key.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:48:04 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/31 18:36:40 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	close_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_terminate(game->mlx);
	exit(0);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	else if (keydata.key == MLX_KEY_UP)
		move_player(game, 0, -1);
	else if (keydata.key == MLX_KEY_DOWN)
		move_player(game, 0, 1);
	else if (keydata.key == MLX_KEY_LEFT)
		move_player(game, -1, 0);
	else if (keydata.key == MLX_KEY_RIGHT)
		move_player(game, 1, 0);
}

void	move_player(t_game *game, int dx, int dy)
{
	t_pos	pos;
	int		new_x;
	int		new_y;
	int		prev_count;

	pos = find_player(game->grid, game->height);
	new_x = pos.x + dx;
	new_y = pos.y + dy;
	prev_count = game->move_count;
	handle_player_move(game, pos, new_x, new_y);
	if (game->move_count > prev_count)
	{
		ft_printf("Moves: %d\n", game->move_count);
		render_map(game);
	}
}

void	handle_player_move(t_game *game, t_pos old_pos, int new_x, int new_y)
{
	char	next;

	next = game->grid[new_y][new_x];
	if (next == '1')
		return ;
	if (next == 'C')
	{
		game->item--;
		game->grid[new_y][new_x] = '0';
	}
	if (game->map[old_pos.y][old_pos.x] == 'E')
		game->grid[old_pos.y][old_pos.x] = 'E';
	else
		game->grid[old_pos.y][old_pos.x] = '0';
	if (next == 'E')
	{
		if (game->item == 0)
			win_game(game);
	}
	game->grid[new_y][new_x] = 'P';
	game->player_img->instances[0].x = new_x * 64;
	game->player_img->instances[0].y = new_y * 64;
	game->move_count++;
}
// void	handle_player_move(t_game *game, t_pos old_pos, int new_x, int new_y)
// {
// 	char	next;

// 	next = game->grid[new_y][new_x];
// 	if (next == '1')
// 		return ;
// 	if (next == 'C')
// 	{
// 		game->item--;
// 		game->grid[new_y][new_x] = '0';
// 	}
// 	if (next == 'E')
// 	{
// 		if (game->item == 0)
// 		{
// 			write(1, "You win!\n", 9);
// 			mlx_terminate(game->mlx);
// 			exit(0);
// 		}
// 		return ;
// 	}
// 	game->grid[old_pos.y][old_pos.x] = '0';
// 	game->grid[new_y][new_x] = 'P';
// 	game->player_img->instances[0].x = new_x * 64;
// 	game->player_img->instances[0].y = new_y * 64;
// 	game->move_count++;
// }

void	count_items(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	game->item = 0;
	while (y < game->height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'C')
				game->item++;
			x++;
		}
		y++;
	}
}
