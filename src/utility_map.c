/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility_map.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 15:44:10 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/02 15:44:34 by jde-groo      ########   odam.nl         */
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
	ret = ft_split(raw, '\n');
	free(raw);
	return (ret);
}
