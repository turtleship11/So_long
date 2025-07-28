void	free_map(char **map)
{
	size_t i = 0;

	if (!map)
		return;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}


#include <stdlib.h>

void dfs(char **grid, int x, int y, t_validation *check)
{
	if (grid[y][x] == '1' || grid[y][x] == 'V') // 벽이거나 방문한 곳
		return ;

	if (grid[y][x] == 'E')
		check->found_exit = 1;
	else if (grid[y][x] == 'C')
		check->found_items++;

	grid[y][x] = 'V'; // 방문 표시

	dfs(grid, x + 1, y, check);
	dfs(grid, x - 1, y, check);
	dfs(grid, x, y + 1, check);
	dfs(grid, x, y - 1, check);
}

char **copy_grid(char **src, size_t height)
{
	char **copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return NULL;
	for (size_t i = 0; i < height; i++)
		copy[i] = ft_strdup(src[i]);
	copy[height] = NULL;
	return copy;
}

void free_grid(char **grid)
{
	size_t i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}

t_pos find_player(char **grid, size_t height)
{
	t_pos pos;
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; grid[y][x]; x++)
		{
			if (grid[y][x] == 'P')
			{
				pos.x = x;
				pos.y = y;
				return pos;
			}
		}
	}
	pos.x = -1;
	pos.y = -1;
	return pos; // 못 찾은 경우
}

int is_map_playable(t_game *game)
{
	char **temp_grid = copy_grid(game->grid, game->height);
	if (!temp_grid)
		return (0);

	t_validation check = {0, 0};
	t_pos start = find_player(temp_grid, game->height);
	if (start.x == -1 || start.y == -1)
	{
		free_grid(temp_grid);
		return (0);
	}

	dfs(temp_grid, start.x, start.y, &check);
	free_grid(temp_grid);

	// 모든 아이템에 도달했고 출구도 찾았는지 확인
	if (check.found_items == game->item_count && check.found_exit)
		return (1);
	else
		return (0);
}
