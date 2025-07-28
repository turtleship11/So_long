/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:45:30 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/26 17:59:10 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./MLX42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include "../libft/libft.h"
#include "../libft/get_next_line.h" //check before push
#include <errno.h>


typedef struct s_pos {
    int x;
    int y;
} t_pos;

typedef struct s_validation {
	int found_exit;
	int found_items;
} t_validation;

typedef	struct s_game
{
	mlx_t	*mlx;
	char	**grid;
	size_t	width;
	size_t	height;
	size_t	item;
	size_t	exit;
	char	**map;
}	t_game ;


int is_map_playable(t_game *game);
#endif
