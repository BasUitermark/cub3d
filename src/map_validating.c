/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validating.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 18:28:19 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/03 16:02:16 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_direction(t_map *map, t_player *player, t_ipos *pos)
{
	player->location.x = (double)pos->x;
	player->location.y = (double)pos->y;
	player->direction.x = -1.0; // kifesh? (south)
	player->direction.y = 0.0;
	/*
	 * hoe de neuk werkt deze ding?
	 * ik weet niet
	 */
	map->map[pos->y][pos->x] = '0';
}

static bool	check_players(t_cub3d *cub3d)
{
	t_ipos	pos;

	pos.y = 0;
	while (cub3d->map.map[pos.y])
	{
		pos.x = 0;
		while (cub3d->map.map[pos.y][pos.x])
		{
			if (ft_strchr("NESW", cub3d->map.map[pos.y][pos.x]))
			{
				if (cub3d->player.location.x == (double)0 || \
					cub3d->player.location.y == (double)0)
					set_player_direction(&cub3d->map, &cub3d->player, &pos);
				else
					return (false);
			}
			pos.x++;
		}
		pos.y++;
	}
	return (cub3d->player.location.x != 0 && cub3d->player.location.y != 0);
}

static bool	cnb(t_cub3d *cub3d, int x, int y, const char *illegal)
{
	if (ft_strchr(illegal, cub3d->map.map[y + 1][x]))
		return (false);
	if (ft_strchr(illegal, cub3d->map.map[y][x + 1]))
		return (false);
	return (true);
}

static bool	check_structure(t_cub3d *cub3d)
{
	int		y;
	int		x;

	y = 0;
	while (y < cub3d->map.dimensions.y - 1)
	{
		x = 0;
		while (x < cub3d->map.dimensions.x - 1)
		{
			if ((cub3d->map.map[y][x] == ' ' && !cnb(cub3d, x, y, "0NESW")) || \
				(cub3d->map.map[y][x] == '0' && !cnb(cub3d, x, y, " ")) || \
				(cub3d->map.map[y][x] == 'N' && !cnb(cub3d, x, y, " ")) || \
				(cub3d->map.map[y][x] == 'E' && !cnb(cub3d, x, y, " ")) || \
				(cub3d->map.map[y][x] == 'S' && !cnb(cub3d, x, y, " ")) || \
				(cub3d->map.map[y][x] == 'W' && !cnb(cub3d, x, y, " ")))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	validate_map(t_cub3d *cub3d)
{
	if (!check_players(cub3d))
		return (perr("invalid amount of players", false));
	if (!check_structure(cub3d))
		return (perr("illegal map", false));
	return (true);
}
