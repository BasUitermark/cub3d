/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 13:26:25 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/06 16:59:09 by jde-groo      ########   odam.nl         */
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

static double		rotSpeed	= 0.06;
static double		movSpeed	= 0.05;

void	test(t_cub3d *cub3d)
{
	(void)cub3d;
	int			index	= 0;
	t_player	*player	= &cub3d->player;
	t_map		*map	= &cub3d->map;
	ft_memset(cub3d->foreground->pixels, 0, cub3d->foreground->width * cub3d->foreground->height * sizeof(int));

	while (index < WIDTH)
	{
		//calculate ray position and direction
		double cameraX = 2 * index / (double)WIDTH - 1; //x-coordinate in camera space
		double rayDirX = player->direction.x + player->plane.x * cameraX;
		double rayDirY = player->direction.y + player->plane.y * cameraX;
		//which box of the map we're in
		int mapX = (int)player->location.x;
		int mapY = (int)player->location.y;
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player->location.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->location.x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player->location.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player->location.y) * deltaDistY;
		}
		//perform DDA
		while(hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(map->map[mapY][mapX] == '1') hit = 1;
		}
		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);
		//Calculate height of line to draw on screen
		int lineHeight = (int)(HEIGHT / perpWallDist);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;
		//choose wall color
		int color = 0x00000000;
		if (map->map[mapY][mapX] == '1')
			color = 0x555555FF;
		if (color && side == 1)
			color = 0x999999FF;
		//draw the pixels of the stripe as a vertical line
		// verLine(x, drawStart, drawEnd, color);
		if (drawEnd < 0)
			drawEnd = HEIGHT - 1;

		double wallX; //where exactly the wall was hit
		if(side == 0) wallX = player->location.y + perpWallDist * rayDirY;
		else          wallX = player->location.x + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		if (index == WIDTH / 2) {
			// printf("%d , %d , %d, 0x%X\n", index, drawStart, drawEnd, color);
			// printf("plane  x %.2f , y %.2f \n", player->plane.x, player->plane.y);
			// printf("player x %.2f , y %.2f \n", player->direction.x, player->direction.y);
			printf("wall x: %.2f\n", wallX);
			if (!side && rayDirX >= 0)
				color = 0xFF0000FF; // north
			else if (!side && rayDirX < 0)
				color = 0x00FF00FF; // south
			else if (side && rayDirY >= 0)
				color = 0x0000FFFF; // west
			else
				color = 0xFFFF00FF; // east
		}
		if (drawEnd < 0 || drawEnd > HEIGHT || drawStart < 0 || drawStart > HEIGHT)
		{
			index++;
			continue ;
		}
		while (drawStart < drawEnd)
		{
			mlx_put_pixel(cub3d->foreground, index, drawStart, color);
			drawStart++;
		}
		index++;
	}
}

void	hook(void *param)
{
	t_cub3d		*cub3d;
	t_player	*player;

	cub3d = (t_cub3d *)param;
	player = &cub3d->player;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub3d->mlx);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->direction.x;
		player->direction.x = player->direction.x * cos(rotSpeed) - player->direction.y * sin(rotSpeed);
		player->direction.y = oldDirX * sin(rotSpeed) + player->direction.y * cos(rotSpeed);
		double oldPlane = player->plane.x;
		player->plane.x = player->plane.x * cos(rotSpeed) - player->plane.y * sin(rotSpeed);
		player->plane.y = oldPlane * sin(rotSpeed) + player->plane.y * cos(rotSpeed);
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
	{
      //both camera direction and camera plane must be rotated
      double oldDirX = player->direction.x;
      player->direction.x = player->direction.x * cos(-rotSpeed) - player->direction.y * sin(-rotSpeed);
      player->direction.y = oldDirX * sin(-rotSpeed) + player->direction.y * cos(-rotSpeed);
      double oldPlane = player->plane.x;
      player->plane.x = player->plane.x * cos(-rotSpeed) - player->plane.y * sin(-rotSpeed);
      player->plane.y = oldPlane * sin(-rotSpeed) + player->plane.y * cos(-rotSpeed);
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_UP))
	{
		player->location.x += player->direction.x * movSpeed;
		player->location.y += player->direction.y * movSpeed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_DOWN))
	{
		player->location.x -= player->direction.x * movSpeed;
		player->location.y -= player->direction.y * movSpeed;
	}
	// printf("player dir x: %f\n", player->direction.x);
	// printf("player dir y: %f\n", player->direction.y);
	test(cub3d);
}

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

	mlx_image_to_window(cub3d->mlx, cub3d->background, 0, 0);
	mlx_image_to_window(cub3d->mlx, cub3d->foreground, 0, 0);
	mlx_loop_hook(cub3d->mlx, &hook, cub3d);
	mlx_loop(cub3d->mlx);
}

int	main(const int argc, const char *argv[])
{
	t_cub3d		cub3d;

	ft_memset(&cub3d, 0, sizeof(t_cub3d));
	if (argc != 2)
		return ((printf("usage: ./cub3d <map>\n") & 0) | EXIT_FAILURE);
	if (!parse_map(&cub3d, argv[1]) || \
		!validate_map(&cub3d) || \
		!load_textures(&cub3d) || \
		!setup(&cub3d))
		return (cleanup(&cub3d, EXIT_FAILURE));
	debug(&cub3d);
	return (cleanup(&cub3d, EXIT_SUCCESS));
}
