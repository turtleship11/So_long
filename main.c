/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:13:29 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/26 18:00:29 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"


int		main(int ac, char **av)
{
	if (av != 2)
	{
		write(2, "Input error, put only map\n", 26);
		return (-1);
	}
	map_check(av[1]);
	
}
char	**read_map(char *av)
{
	int	fd;
	char **map;
	char *line;
	char *map_str;
	char *temp;

	fd = open(av, O_RDONLY);
	if (fd == -1 || errno == EISDIR)
	{
		write(2, "Invalid map file\n", 17);
		return (NULL);
	}
	map_str = ft_strdup("");
	if (!map_str)
	{
		write(2,"strdup error\n", 13);
		exit(-1);
	}
	while ((line = get_next_line(fd)))
	{
		temp = map_str;
		map_str = ft_strjoin(map_str, line);
		free(temp);
		free(line);
	}
	close(fd);
	map = ft_split(map_str, '\n');
	free(map_str);
	return (map);
}

t_game	init_map(char *av)
{
	t_game	game;
	char *temp;
	char *map_str;

	game.map = read_map(av);
	if (!game.map)
	{
		write(2, "Map reading failed\n", 20);
		exit(-1);	
	}
	return (game);
}

int		map_check(char *av)
{
	int	len;
	char *format;
	
	format = ".ber";
	len = 0;
	len = ft_strlen(av);
	if (len <= 4)
	{
		write(2,"file name error\n",16);
		exit(-1);
	}
	if (ft_strncmp(&av[len - 4], format, 4) != 0)
	{
		write(2,"file name error\n",16);
		exit(-1);		
	}
	return (1);
}


// #define WIDTH 512
// #define HEIGHT 512

// static mlx_image_t* image;

// // -----------------------------------------------------------------------------

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

// void ft_randomize(void* param)
// {
// 	(void)param;
// 	for (uint32_t i = 0; i < image->width; ++i)
// 	{
// 		for (uint32_t y = 0; y < image->height; ++y)
// 		{
// 			uint32_t color = ft_pixel(
// 				rand() % 0xFF, // R
// 				rand() % 0xFF, // G
// 				rand() % 0xFF, // B
// 				rand() % 0xFF  // A
// 			);
// 			mlx_put_pixel(image, i, y, color);
// 		}
// 	}
// }

// void ft_hook(void* param)
// {
// 	mlx_t* mlx = param;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		image->instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		image->instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		image->instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		image->instances[0].x += 5;
// }

// // -----------------------------------------------------------------------------

// int32_t main(void)
// {
// 	mlx_t* mlx;

// 	// Gotta error check this stuff
// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(image = mlx_new_image(mlx, 128, 128)))
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
	
// 	mlx_loop_hook(mlx, ft_randomize, mlx);
// 	mlx_loop_hook(mlx, ft_hook, mlx);

// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }
