/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 15:11:51 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/02 17:38:57 by jde-groo      ########   odam.nl         */
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
	if (!mlx)
		return ;
	mlx_terminate(mlx);
}

int	cleanup(t_cub3d *cub3d, int exit_code)
{
	free_map(&cub3d->map);
	free_mlx(cub3d->mlx);
	return (exit_code);
}
