/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   location_validating.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: buiterma <buiterma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/04 17:05:43 by buiterma      #+#    #+#                 */
/*   Updated: 2023/03/11 14:08:30 by buiterma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_location(double x, double y, t_cub3d *cub3d)
{
	if (cub3d->map.map[(int)floor(y)][(int)floor(x)] == '1')
		return (FALSE);
	return (TRUE);
}
