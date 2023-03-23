/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_characters.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 13:36:16 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/23 10:52:09 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_map_characters(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->dimensions.y)
	{
		x = 0;
		while (x < map->dimensions.x)
		{
			if (!ft_strchr(" 01NESW", map->map[y][x]))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}
