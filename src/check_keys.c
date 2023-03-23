/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_keys.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 13:42:14 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/23 10:56:04 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_occurences(char **raw, const char *key)
{
	int	found;
	int	index;

	index = 0;
	found = 0;
	while (raw[index])
	{
		if (ft_strncmp(raw[index], key, ft_strlen(key)) == 0)
			found++;
		index++;
	}
	return (found);
}

// check for duplicate keys
// check for invalid keys eg. "LOL textures/etc..."
// **raw = mapfile splitted by \n
bool	check_keys(char **raw)
{
	if (find_occurences(raw, "NO ") != 1 || \
		find_occurences(raw, "EA ") != 1 || \
		find_occurences(raw, "SO ") != 1 || \
		find_occurences(raw, "WE ") != 1 || \
		find_occurences(raw, "F ") != 1 || \
		find_occurences(raw, "C ") != 1)
		return (false);
	return (true);
}
