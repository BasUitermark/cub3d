/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_keys.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 13:42:14 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/23 12:02:03 by jde-groo      ########   odam.nl         */
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

static bool	only_contains(char *targ, char *chars)
{
	int	index;

	index = 0;
	while (targ[index])
	{
		if (!ft_strchr(chars, targ[index]))
			return (false);
		index++;
	}
	return (true);
}

static bool	check_invalid_keys(char **raw)
{
	int	index;

	index = 0;
	while (raw[index])
	{
		if (!only_contains(raw[index], " 01NESW") && \
			ft_strncmp(raw[index], "NO ", 3) != 0 && \
			ft_strncmp(raw[index], "EA ", 3) != 0 && \
			ft_strncmp(raw[index], "SO ", 3) != 0 && \
			ft_strncmp(raw[index], "WE ", 3) != 0 && \
			ft_strncmp(raw[index], "F ", 2) != 0 && \
			ft_strncmp(raw[index], "C ", 2) != 0)
			return (false);
		index++;
	}
	return (true);
}

bool	check_keys(char **raw)
{
	if (find_occurences(raw, "NO ") != 1 || \
		find_occurences(raw, "EA ") != 1 || \
		find_occurences(raw, "SO ") != 1 || \
		find_occurences(raw, "WE ") != 1 || \
		find_occurences(raw, "F ") != 1 || \
		find_occurences(raw, "C ") != 1 || \
		!check_invalid_keys(raw))
		return (false);
	return (true);
}
