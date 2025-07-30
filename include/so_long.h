/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:45:30 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/29 15:09:21 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../MLX42/include/MLX42/MLX42.h"
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
	int	item;
	int	exit;
	char	**map;

	mlx_image_t *wall_img;
	mlx_image_t *floor_img;
	mlx_image_t *player_img;
	mlx_image_t *item_img;
	mlx_image_t *exit_img;
}	t_game ;

typedef struct s_textures
{
    mlx_texture_t *wall;
    mlx_texture_t *floor;
    mlx_texture_t *player;
    mlx_texture_t *item;
    mlx_texture_t *exit;
} t_textures;

int is_map_playable(t_game *game);
int		map_check(char *av);
t_game	init_map(char *av);
void	read_map(t_game *game, char *filename);
int get_map_height(const char *filename);
char	*read_map_str(const char *filename);
char **copy_grid(char **src, size_t height);
void copy_map_to_grid(t_game *game);
int	validate_map(t_game game);
void	free_map(char **map);
void load_textures(t_textures *textures);
void draw_tile(t_game *game, mlx_image_t *img, int x, int y);
void create_images(t_game *game, t_textures *textures);
void render_map(t_game *game);
void cleanup_images(t_game *game);
void cleanup_textures(t_textures *textures);
t_pos find_player(char **grid, size_t height);
void	move_player(t_game *game, int dx, int dy);
void dfs(char **grid, int x, int y, t_validation *check);
int	validate_map(t_game game);

#endif
