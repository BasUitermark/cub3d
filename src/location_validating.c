/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   location_validating.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: buiterma <buiterma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/04 17:05:43 by buiterma      #+#    #+#                 */
/*   Updated: 2023/03/05 13:22:43 by buiterma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_location(double x, double y, t_cub3d *cub3d)
{
	if (x)
	{
		if (x - cub3d->movSpeed < 1 || \
		x + cub3d->movSpeed > cub3d->map.dimensions.x - 1)
			return (FALSE);
		return (TRUE);
	}
	else if (y)
	{
		if (y - cub3d->movSpeed < 1 || \
		y + cub3d->movSpeed > cub3d->map.dimensions.y - 1)
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}
