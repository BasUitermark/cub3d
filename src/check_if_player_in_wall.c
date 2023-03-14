/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_if_player_in_wall.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 16:18:36 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/14 16:20:43 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_if_player_in_wall(t_map *map, t_player *player)
{
	if ((int)player->location.x == 0 || \
		(int)player->location.x == map->dimensions.x - 1)
		return (false);
	if ((int)player->location.y == 0 || \
		(int)player->location.y == map->dimensions.y - 1)
		return (false);
	return (true);
}
