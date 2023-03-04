/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 11:24:20 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/04 10:37:21 by buiterma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	load_textures_fr(t_cub3d *cub3d)
{
	int		index;

	index = 0;
	while (index < 4)
	{
		if (!cub3d->map.textures[index])
			return (perr(BOLD "\tUnparsed texture\n" RESET, false));
		cub3d->textures[index] = mlx_load_png(cub3d->map.textures[index]);
		if (!cub3d->textures[index])
			return (perr(BOLD "\tFailed loading texture\n" RESET, false));
		index++;
	}
	return (true);
}

bool	load_textures(t_cub3d *cub3d)
{
	if (!load_textures_fr(cub3d))
		return (false);
	return (true);
}
