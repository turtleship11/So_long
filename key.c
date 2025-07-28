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
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        mlx_close_window(game->mlx);
    }

    // TODO: 여기에 플레이어 움직임 처리 코드 추가
}
