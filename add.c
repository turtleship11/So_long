/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:09:01 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/29 15:09:09 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_map(t_game game)
{
	int		player = 0;
	int		exit = 0;
	int		item = 0;
	size_t	i = 0;

	while (i < game.height)
	{
		if ((int)ft_strlen(game.grid[i]) != (int)game.width)
		{
			write(2, "Error: Map is not rectangular\n", 30);
			return (0);
		}

		size_t j = 0;
		while (j < game.width)
		{
			char c = game.grid[i][j];

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
				exit++;
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
		return (0);
	}
	if (exit < 1)
	{
		write(2, "Error: There must be at least one exit\n", 39);
		return (0);
	}
	if (item < 1)
	{
		write(2, "Error: There must be at least one collectible\n", 46);
		return (0);
	}
	return (1);
}
//맵 렌더링 (GML == MLX)
//mlx_put_image_to_window를 사용해서 각 요소마다 이미지 지정해서 출력
//1.ber 맵 파일을 읽고
//2.2차원 배열로 저장
//3.벽, 플레이어, 아이템, 출구 등 맵 구성 요소 확인
//4.유효한 맵인지 검사
//5.이후 GML (Game Map Loader X 없이 직접 그리기) 혹은 mlx로 그리기
