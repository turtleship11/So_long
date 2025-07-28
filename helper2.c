#include "so_long.h"

typedef struct s_textures
{
    mlx_texture_t *wall;
    mlx_texture_t *floor;
    mlx_texture_t *player;
    mlx_texture_t *item;
    mlx_texture_t *exit;
} t_textures;

void load_textures(t_game *game, t_textures *textures)
{
    textures->wall = mlx_load_png("textures/wall.png");
    textures->floor = mlx_load_png("textures/floor.png");
    textures->player = mlx_load_png("textures/player.png");
    textures->item = mlx_load_png("textures/item.png");
    textures->exit = mlx_load_png("textures/exit.png");

    if (!textures->wall || !textures->floor || !textures->player || !textures->item || !textures->exit)
    {
        write(2, "Failed to load textures\n", 24);
        exit(EXIT_FAILURE);
    }
}

void draw_tile(t_game *game, t_textures *textures, int x, int y, mlx_texture_t *texture)
{
    mlx_image_t *img = mlx_new_image(game->mlx, 64, 64);
    if (!img)
    {
        write(2, "Failed to create image\n", 23);
        exit(EXIT_FAILURE);
    }
    mlx_texture_to_image(game->mlx, img, texture, 0);
    mlx_image_to_window(game->mlx, img, x * 64, y * 64);
}

void render_map(t_game *game, t_textures *textures)
{
    size_t  x;
    size_t  y;
    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            char tile = game->grid[y][x];
            if (tile == '1')
                draw_tile(game, textures, x, y, textures->wall);
            else if (tile == '0')
                draw_tile(game, textures, x, y, textures->floor);
            else if (tile == 'P')
                draw_tile(game, textures, x, y, textures->player);
            else if (tile == 'C')
                draw_tile(game, textures, x, y, textures->item);
            else if (tile == 'E')
                draw_tile(game, textures, x, y, textures->exit);
            x++;
        }
        y++;
    }
}
