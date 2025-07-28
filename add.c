
typedef struct s_map {
    char **grid;
    int width;
    int height;
}   t_map;

char *get_next_line(int fd); // 필요시 구현하거나 외부에서 가져오기

int get_map_height(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0) return -1;

    int height = 0;
    char *line;
    while ((line = get_next_line(fd)))
    {
        height++;
        free(line);
    }
    close(fd);
    return height;
}

t_map *read_map(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0) return NULL;

    int height = get_map_height(filename);
    if (height <= 0) return NULL;

    t_map *map = malloc(sizeof(t_map));
    if (!map) return NULL;
    map->height = height;
    map->grid = malloc(sizeof(char *) * (height + 1));

    int i = 0;
    char *line;
    while ((line = get_next_line(fd)))
    {
        map->grid[i++] = line;
    }
    map->grid[i] = NULL;
    if (i > 0)
        map->width = strlen(map->grid[0]);
    else
        map->width = 0;
    close(fd);
    return map;
}

void free_map(t_map *map)
{
    if (!map) return;
    for (int i = 0; i < map->height; i++)
        free(map->grid[i]);
    free(map->grid);
    free(map);
}


// 맵 유효성 검사 (예시) 1로 벽으로 둘러싸여 있는지
//P는 하나만 존재해야 함 E, C는 최소 1개 이상
int validate_map(t_map *map)
{
    int player_count = 0;
    int exit_count = 0;
    int collect_count = 0;

    for (int i = 0; i < map->height; i++) {
        if ((int)strlen(map->grid[i]) != map->width)
            return 0; // Not a rectangle
        for (int j = 0; j < map->width; j++) {
            char c = map->grid[i][j];
            if (i == 0 || i == map->height - 1 || j == 0 || j == map->width - 1) {
                if (c != '1') return 0; // Walls must be on the border
            }
            if (c == 'P') player_count++;
            if (c == 'E') exit_count++;
            if (c == 'C') collect_count++;
        }
    }

    return (player_count == 1 && exit_count >= 1 && collect_count >= 1);
}

//맵 렌더링 (GML == MLX)
//mlx_put_image_to_window를 사용해서 각 요소마다 이미지 지정해서 출력
//1.ber 맵 파일을 읽고
//2.2차원 배열로 저장
//3.벽, 플레이어, 아이템, 출구 등 맵 구성 요소 확인
//4.유효한 맵인지 검사
//5.이후 GML (Game Map Loader X 없이 직접 그리기) 혹은 mlx로 그리기