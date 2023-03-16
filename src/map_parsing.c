/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parsing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 14:45:58 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/16 13:26:40 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*parse_element(t_cub3d *cub3d, const char *key)
{
	int		n[3];

	n[0] = 0;
	while (cub3d->map.raw_map[n[0]] && \
		0 != ft_strncmp(cub3d->map.raw_map[n[0]], key, ft_strlen(key)))
		n[0]++;
	if (!cub3d->map.raw_map[n[0]])
		return (NULL);
	n[1] = 0;
	while (cub3d->map.raw_map[n[0]][n[1]] && \
		cub3d->map.raw_map[n[0]][n[1]] != ' ')
		n[1]++;
	while (cub3d->map.raw_map[n[0]][n[1]] && \
		(!ft_isprint(cub3d->map.raw_map[n[0]][n[1]]) || \
		cub3d->map.raw_map[n[0]][n[1]] == ' '))
		n[1]++;
	if (!cub3d->map.raw_map[n[0]][n[1]])
		return (NULL);
	n[2] = 0;
	while (cub3d->map.raw_map[n[0]][n[1] + n[2]] && \
		ft_isprint(cub3d->map.raw_map[n[0]][n[1] + n[2]]) && \
		cub3d->map.raw_map[n[0]][n[1] + n[2]] != ' ')
		n[2]++;
	cub3d->map.raw_map[n[0]][n[1] + n[2]] = '\0';
	return (ft_strdup(&cub3d->map.raw_map[n[0]][n[1]]));
}

static bool	parse_color(int *res, char *rgb)
{
	char	**sep;

	if (!rgb || !check_if_there_are_two_commas(rgb))
		return (false);
	sep = ft_split(rgb, ',');
	free(rgb);
	if (!sep || array_len(sep) != 3)
		return (array_free(sep));
	if ((ft_atoi(sep[0]) > 255 || ft_atoi(sep[0]) < 0) || \
		(ft_atoi(sep[1]) > 255 || ft_atoi(sep[1]) < 0) || \
		(ft_atoi(sep[2]) > 255 || ft_atoi(sep[2]) < 0))
		return (array_free(sep));
	res[0] = (ft_atoi(sep[0]) << 24) | (ft_atoi(sep[1]) << 16) | \
		(ft_atoi(sep[2]) << 8) | 0x000000FF;
	array_free(sep);
	return (true);
}

static bool	set_map_dimensions(t_map *map)
{
	int		index[3];

	ft_memset(&index, 0, sizeof(index));
	while (map->raw_map[index[0]] && !index[2])
	{
		index[1] = 0;
		index[2] = 1;
		while (map->raw_map[index[0]][index[1]])
			if (!ft_strrchr(" 01NESW", map->raw_map[index[0]][index[1]++]))
				index[2] = 0;
		index[0]++;
	}
	index[0]--;
	while (map->raw_map[index[0] + map->dimensions.y])
		map->dimensions.y++;
	while (map->raw_map[index[0]])
	{
		if ((int)ft_strlen(map->raw_map[index[0]]) > map->dimensions.x)
			map->dimensions.x = ft_strlen(map->raw_map[index[0]]);
		index[0]++;
	}
	if (map->dimensions.x <= 1 || map->dimensions.x <= 1)
		return (false);
	return (true);
}

static bool	parse_map_frfr(t_map *map)
{
	int		index;

	if (!set_map_dimensions(map))
		return (false);
	map->map = ft_calloc(map->dimensions.y + 1, sizeof(char *));
	if (!map->map)
		return (false);
	index = 0;
	while (index < map->dimensions.y)
		map->map[index++] = ft_calloc(map->dimensions.x + 1, sizeof(char));
	index = 0;
	while (index < map->dimensions.y)
	{
		ft_memset(map->map[index], ' ', map->dimensions.x);
		ft_memcpy(map->map[index], map->raw_map[array_len(map->raw_map) \
			- map->dimensions.y + index], ft_strlen(map->raw_map[\
			array_len(map->raw_map) - map->dimensions.y + index]));
		index++;
	}
	return (true);
}

bool	parse_map(t_cub3d *cub3d, const char *map)
{
	if (ft_strlen(map) < 5 || ft_strncmp(&map[ft_strlen(map) - 4], ".cub", 4))
		return (perr(BOLD "\tInvalid filename\n" RESET, false));
	cub3d->map.raw_map = read_map(map);
	if (!cub3d->map.raw_map)
		return (perr(BOLD "\tFailed reading map\n" RESET, false));
	if (!parse_color(&cub3d->map.floor, parse_element(cub3d, "F")) || \
		!parse_color(&cub3d->map.ceiling, parse_element(cub3d, "C")))
		return (perr(BOLD "\tFailed parsing colors\n" RESET, false));
	cub3d->map.textures[0] = parse_element(cub3d, "NO");
	cub3d->map.textures[1] = parse_element(cub3d, "EA");
	cub3d->map.textures[2] = parse_element(cub3d, "SO");
	cub3d->map.textures[3] = parse_element(cub3d, "WE");
	if (!parse_map_frfr(&cub3d->map))
		return (perr(BOLD "\tFailed parsing map\n" RESET, false));
	return (true);
}
