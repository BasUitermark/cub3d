/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 15:11:51 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/01 15:22:28 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(t_map *map)
{
	int	index;

	index = 0;
	if (map->map)
		while (map->map[index])
			free(map->map[index++]);
	index = 4;
	while (index)
		free(map->textures[--index]);
}

int	cleanup(t_cub3d *cub3d, int exit_code)
{
	free_map(&cub3d->map);
	return (exit_code);
}
