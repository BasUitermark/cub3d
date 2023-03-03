/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics_setup.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 12:13:45 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/03 14:46:42 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_background(mlx_image_t *image, t_map *map)
{
	int		index;

	index = 0;
	while (index < HEIGHT * WIDTH / 2)
	{
		mlx_put_pixel(image, index % WIDTH, index / WIDTH, map->ceiling);
		mlx_put_pixel(image, index % WIDTH, index / WIDTH + \
			HEIGHT / 2, map->floor);
		index++;
	}
}

bool	setup(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!cub3d->mlx)
		return (perr("failed initializing mlx", false));
	cub3d->background = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->background)
		return (perr("failed creating background image", false));
	cub3d->foreground = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->foreground)
		return (perr("failed creating foreground image", false));
	set_background(cub3d->background, &cub3d->map);
	return (true);
}
