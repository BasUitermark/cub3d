/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 13:26:25 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/02 18:39:55 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <memory.h>
// #include "MLX42/MLX42.h"
// #define WIDTH 512
// #define HEIGHT 512

// static mlx_image_t* img;

// void hook(void* param)
// {
// 	mlx_t* mlx = param;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		img->instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		img->instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		img->instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		img->instances[0].x += 5;
// }

// int32_t	main(void)
// {
// 	mlx_t* mlx;

// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 		return(EXIT_FAILURE);

// 	img = mlx_new_image(mlx, 128, 128);
// 	memset(img->pixels, 255, img->width * img->height * sizeof(int));
// 	mlx_image_to_window(mlx, img, 0, 0);

// 	mlx_loop_hook(mlx, &hook, mlx);
// 	mlx_loop(mlx);

// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }

#include "cub3d.h"
#include "libft.h"

static void	debug(t_cub3d *cub3d)
{
	printf("texture 0  : '%s'\n", cub3d->map.textures[0]);
	printf("texture 1  : '%s'\n", cub3d->map.textures[1]);
	printf("texture 2  : '%s'\n", cub3d->map.textures[2]);
	printf("texture 3  : '%s'\n", cub3d->map.textures[3]);
	printf("color C    : '0x%X'\n", cub3d->map.ceiling);
	printf("color F    : '0x%X'\n", cub3d->map.floor);
	printf("map width  : %d \n", cub3d->map.dimensions.x);
	printf("map height : %d \n", cub3d->map.dimensions.y);

	printf("map        : ");
	for (int i = 0; i < cub3d->map.dimensions.x + 2; i++)
		printf("-");
	printf("\n");
	for (int i = 0; i < cub3d->map.dimensions.y; i++)
		printf("           : |%s|\n", cub3d->map.map[i]);
	printf("           : ");
	for (int i = 0; i < cub3d->map.dimensions.x + 2; i++)
		printf("-");
	printf("\n");
}

int	main(const int argc, const char *argv[])
{
	t_cub3d		cub3d;

	ft_memset(&cub3d, 0, sizeof(t_cub3d));
	if (argc != 2)
		return ((printf("usage: ./cub3d <map>\n") & 0) | EXIT_FAILURE);
	if (!parse_map(&cub3d, argv[1]))
		return (cleanup(&cub3d, EXIT_FAILURE));
	if (!validate_map(&cub3d))
		return (cleanup(&cub3d, EXIT_FAILURE));
	// cub3d.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	// if (!cub3d.mlx)
	// 	return (cleanup(&cub3d, EXIT_FAILURE));
	debug(&cub3d);
	return (cleanup(&cub3d, EXIT_SUCCESS));
}
