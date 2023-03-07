/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   location_validating.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: buiterma <buiterma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/04 17:05:43 by buiterma      #+#    #+#                 */
/*   Updated: 2023/03/07 17:59:47 by buiterma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_location_new(double x, double y, t_cub3d *cub3d)
{
	// printf(GREEN BOLD "Player X: %f/%d\n" RESET, x, (int)floor(x));
	// printf(BLUE BOLD "Player Y: %f/%d\n" RESET, y, (int)floor(y));
	// printf(RED BOLD "Map Point: %c\n" RESET, cub3d->map.map[(int)floor(y)][(int)floor(x)]);
	if (cub3d->map.map[(int)floor(y)][(int)floor(x)] == '1')
		return (FALSE);
	return (TRUE);
}
