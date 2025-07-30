/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:48:04 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/29 11:48:05 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

void close_hook(void *param)
{
    t_game *game = (t_game *)param;
    mlx_terminate(game->mlx);
    exit(0);
}

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_game *game = (t_game *)param;
	if (keydata.action != MLX_PRESS)
		return ;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	else if (keydata.key == MLX_KEY_W)
		move_player(game, 0, -1);
	else if (keydata.key == MLX_KEY_S)
		move_player(game, 0, 1);
	else if (keydata.key == MLX_KEY_A)
		move_player(game, -1, 0);
	else if (keydata.key == MLX_KEY_D)
		move_player(game, 1, 0);
}


void	move_player(t_game *game, int dx, int dy)
{
	static int move_count = 0;
	t_pos pos = find_player(game->grid, game->height);
	int new_x = pos.x + dx;
	int new_y = pos.y + dy;
	char next = game->grid[new_y][new_x];

	if (next == '1') // 벽이면 무시
		return ;
	if (next == 'C') // 아이템이면 수집
		game->item--;
	if (next == 'E')
	{
		if (game->item == 0)
		{
			write(1, "You win!\n", 9);
			mlx_close_window(game->mlx);
		}
		return ; // 아이템 다 안먹었으면 못 나감
	}

	// 위치 업데이트
	game->grid[pos.y][pos.x] = '0';
	game->grid[new_y][new_x] = 'P';
	game->player_img->instances[0].x = new_x * 64;
	game->player_img->instances[0].y = new_y * 64;

	move_count++;
	ft_printf("Moves: %d\n", move_count);
}
