/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 15:11:51 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/03 14:46:58 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(t_map *map)
{
	int	index;

	array_free(map->map);
	array_free(map->raw_map);
	index = 4;
	while (index)
		free(map->textures[--index]);
}

static void	free_mlx(mlx_t *mlx)
{
	if (mlx)
		mlx_terminate(mlx);
}

static void	free_textures(mlx_texture_t *textures[4])
{
	int		index;

	index = 0;
	while (index < 4)
	{
		if (textures[index])
			mlx_delete_texture(textures[index]);
		index++;
	}
}

static void	free_images(t_cub3d *cub3d)
{
	if (cub3d->background)
		mlx_delete_image(cub3d->mlx, cub3d->background);
	if (cub3d->foreground)
		mlx_delete_image(cub3d->mlx, cub3d->foreground);
}

int	cleanup(t_cub3d *cub3d, int exit_code)
{
	free_map(&cub3d->map);
	free_textures(cub3d->textures);
	free_images(cub3d);
	free_mlx(cub3d->mlx);
	return (exit_code);
}
