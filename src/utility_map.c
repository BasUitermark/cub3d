/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility_map.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 15:44:10 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/16 09:40:31 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*join_free(char *s1, char *s2)
{
	char	*s3;

	if (!s1)
		return (ft_strdup(s2));
	s3 = ft_strjoin(s1, s2);
	free(s1);
	return (s3);
}

static int	find_index_last_texture(char *raw)
{
	int	ti[2];

	ft_memset(ti, 0, sizeof(ti));
	while (raw[ti[1]] && raw[ti[1] + 1] && ti[0] != 0b00111111)
	{
		if (raw[ti[1]] == 'N' && raw[ti[1] + 1] == 'O' && raw[ti[1] + 2] == ' ')
			ti[0] |= 0b00000001;
		if (raw[ti[1]] == 'E' && raw[ti[1] + 1] == 'A' && raw[ti[1] + 2] == ' ')
			ti[0] |= 0b00000010;
		if (raw[ti[1]] == 'S' && raw[ti[1] + 1] == 'O' && raw[ti[1] + 2] == ' ')
			ti[0] |= 0b00000100;
		if (raw[ti[1]] == 'W' && raw[ti[1] + 1] == 'E' && raw[ti[1] + 2] == ' ')
			ti[0] |= 0b00001000;
		if (raw[ti[1]] == 'F' && raw[ti[1] + 1] == ' ')
			ti[0] |= 0b00010000;
		if (raw[ti[1]] == 'C' && raw[ti[1] + 1] == ' ')
			ti[0] |= 0b00100000;
		ti[1]++;
	}
	while (raw[ti[1]] && raw[ti[1]] != '\n')
		ti[1]++;
	if (ti[0] != 0b00111111 || !raw[ti[1]])
		return (0);
	return (ti[1]);
}

// checks if there are new lines in map
static bool	validate_raw_map(char *raw)
{
	int	index;

	index = find_index_last_texture(raw);
	if (!index)
	{
		free(raw);
		return (false);
	}
	while (raw[index] && !ft_strchr(" 01NESW", raw[index]))
		index++;
	if (!raw[index])
		return (false);
	while (raw[index] && !(raw[index] == '\n' && raw[index + 1] == '\n'))
		index++;
	if (!raw[index])
		return (true);
	free(raw);
	return (false);
}

char	**read_map(const char *map)
{
	char	buffer[32];
	char	*raw;
	int		fd_and_r[2];
	char	**ret;

	raw = NULL;
	fd_and_r[0] = open(map, O_RDONLY);
	if (fd_and_r[0] < 0)
		return (NULL);
	fd_and_r[1] = read(fd_and_r[0], buffer, 31);
	while (fd_and_r[1] > 0)
	{
		buffer[fd_and_r[1]] = 0;
		raw = join_free(raw, buffer);
		if (!raw)
			return (NULL);
		fd_and_r[1] = read(fd_and_r[0], buffer, 31);
	}
	if (!raw || !raw[0] || !validate_raw_map(raw))
		return (false);
	ret = ft_split(raw, '\n');
	free(raw);
	return (ret);
}
