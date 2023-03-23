/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_if_player_in_wall.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/14 16:18:36 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/23 13:55:02 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_if_zero_in_wall(t_map *map)
{
	int	index;

	index = 1;
	while (index < map->dimensions.y - 1)
	{
		if (map->map[index][0] == '0' || \
			map->map[index][map->dimensions.x - 1] == '0')
			return (false);
		index++;
	}
	index = 1;
	while (index < map->dimensions.x - 1)
	{
		if (map->map[0][index] == '0' || \
			map->map[map->dimensions.y - 1][index] == '0')
			return (false);
		index++;
	}
	return (true);
}

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
