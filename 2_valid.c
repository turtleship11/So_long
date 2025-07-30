/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_valid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:09:01 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/30 19:20:56 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_map(t_game game)
{
	int		player;
	int		exit_g;
	int		item;
	size_t	i;
	size_t	j;
	char	c;

	player = 0;
	exit_g = 0;
	item = 0;
	i = 0;
	while (i < game.height)
	{
		if ((int)ft_strlen(game.grid[i]) != (int)game.width)
		{
			write(2, "Error: Map is not rectangular\n", 30);
			return (0);
		}
		j = 0;
		while (j < game.width)
		{
			c = game.grid[i][j];
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
				exit_g++;
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
    	exit(1); 
	}
	if (exit_g < 1)
	{
		write(2, "Error: There must be at least one exit\n", 39);
    	exit(EXIT_FAILURE); 
	}
	if (item < 1)
	{
		write(2, "Error: There must be at least one collectible\n", 46);
    	exit(EXIT_FAILURE); 
	}
	return (1);
}
