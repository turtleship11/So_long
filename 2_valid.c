/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_valid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:09:01 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/31 17:55:16 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_map(t_game game)
{
	t_counts	counts;

	counts.player = 0;
	counts.exit_g = 0;
	counts.item = 0;
	if (!check_map_shape(game))
		return (0);
	if (!check_map_contents(game, &counts))
		return (0);
	check_map_elements(counts);
	return (1);
}

int	check_map_shape(t_game game)
{
	size_t	i;

	i = 0;
	while (i < game.height)
	{
		if ((int)ft_strlen(game.grid[i]) != (int)game.width)
		{
			write(2, "Error: Map is not rectangular\n", 30);
			return (0);
		}
		i++;
	}
	return (1);
}

void	check_map_cell(char c, t_pos pos, t_game game, t_counts *counts)
{
	if ((pos.i == 0 || pos.i == game.height - 1 || pos.j == 0
			|| pos.j == game.width - 1) && c != '1')
		return_with_error("Border needs to be wall\n");
	if (c == 'P')
		counts->player++;
	else if (c == 'E')
		counts->exit_g++;
	else if (c == 'C')
		counts->item++;
	else if (c != '0' && c != '1')
		return_with_error("Invalid character in map\n");
}

int	check_map_contents(t_game game, t_counts *counts)
{
	size_t	i;
	size_t	j;
	t_pos	pos;
	char	c;

	i = 0;
	while (i < game.height)
	{
		j = 0;
		while (j < game.width)
		{
			pos.i = i;
			pos.j = j;
			c = game.grid[i][j];
			check_map_cell(c, pos, game, counts);
			j++;
		}
		i++;
	}
	return (1);
}

void	check_map_elements(t_counts counts)
{
	if (counts.player != 1)
		return_with_error("Error: There must be exactly one player\n");
	if (counts.exit_g < 1)
		return_with_error("Error: There must be at least one exit\n");
	if (counts.item < 1)
		return_with_error("Error: There must be at least one collectible\n");
}
