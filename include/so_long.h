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

# include "../MLX42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include "../libft/libft.h"
#include "../libft/get_next_line.h" //check before push
#include <errno.h>


typedef	struct s_game
{
	mlx_t	*mlx;
	char	**grid;
	size_t	wid;
	size_t	hei;
	size_t	p_x;
	size_t	p_y;
	size_t	item;
	char	**map;
}	t_game ;

#endif
