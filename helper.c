/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:29:55 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/31 17:51:58 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	size_t	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

// int	is_map_playable(t_game *game)
// {
// 	t_validation	check;
// 	t_pos			start;
// 	char			**temp_grid;
// 	t_counts		counts;

// 	temp_grid = copy_grid(game->grid, game->height);
// 	if (!temp_grid)
// 		return (0);

// 	check_map_contents(*game, &counts);
// 	// 플레이어 위치 찾기
// 	start = find_player(temp_grid, game->height);
// 	if (start.x == -1 || start.y == -1)
// 	{
// 		ft_printf("Error: 플레이어 위치를 찾을 수 없습니다.\n");
// 		free_map(temp_grid);
// 		return (0);
// 	}

// 	// 디버깅 출력: 플레이어 위치, 아이템 개수
// 	ft_printf("[DEBUG] 플레이어 시작 위치: (%d, %d)\n", start.x, start.y);
// 	ft_printf("[DEBUG] 맵에 존재하는 아이템 개수 (counts->item): %d\n", counts.item);

// 	// DFS 탐색 시작
// 	dfs(temp_grid, start.x, start.y, &check);

// 	// 디버깅 출력: 탐색 후 아이템 발견 개수, 출구 발견 여부
// 	ft_printf("[DEBUG] DFS 탐색 결과 - 발견한 아이템: %d\n", check.found_items);
// 	ft_printf("[DEBUG] ITEM- 발견한 아이템: %d\n", check.found_items);
// 	ft_printf("[DEBUG] DFS 탐색 결과 - 출구 발견 여부: %d\n", check.found_exit);

// 	// 디버깅 출력: 탐색 후 방문 표시된 맵 상태 출력
// 	ft_printf("[DEBUG] DFS 탐색 후 맵 상태:\n");
// 	for (int i = 0; i < (int)game->height; i++)
// 	{
// 		ft_printf("%s\n", temp_grid[i]);
// 	}

// 	// 메모리 해제
// 	free_map(temp_grid);

// 	// 아이템 접근 불가 체크
// 	if (check.found_items != counts.item)
// 		return_with_error("Map is not playable!\n");

// 	// 출구 접근 불가 체크
// 	if (!check.found_exit)
// 		return_with_error("Map is not playable!\n");

// 	// 모든 조건 만족 시 플레이 가능
// 	return (1);
// }

int	is_map_playable(t_game *game)
{
	t_validation	check;
	t_pos			start;
	char			**temp_grid;
	t_counts		counts;

	temp_grid = copy_grid(game->grid, game->height);
	if (!temp_grid)
		return (0);
	check_map_contents(*game, &counts);
	check.found_items = 0;
	check.found_exit = 0;
	start = find_player(temp_grid, game->height);
	if (start.x == -1 || start.y == -1)
	{
		free_map(temp_grid);
		return (0);
	}
	dfs(temp_grid, start.x, start.y, &check);
	free_map(temp_grid);
	if (check.found_items != counts.item)
		return_with_error("Map is not playable!\n");
	if (!check.found_exit)
		return_with_error("Map is not playable!\n");
	return (1);
}

void	dfs(char **grid, int x, int y, t_validation *check)
{
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return ;
	if (grid[y][x] == 'E')
		check->found_exit = 1;
	else if (grid[y][x] == 'C')
		check->found_items++;
	grid[y][x] = 'V';
	dfs(grid, x + 1, y, check);
	dfs(grid, x - 1, y, check);
	dfs(grid, x, y + 1, check);
	dfs(grid, x, y - 1, check);
}

char	**copy_grid(char **src, size_t height)
{
	size_t	i;
	char	**copy;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(src[i]);
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

t_pos	find_player(char **grid, size_t height)
{
	t_pos	pos;
	size_t	y;
	size_t	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == 'P')
			{
				pos.x = x;
				pos.y = y;
				return (pos);
			}
			x++;
		}
		y++;
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}
