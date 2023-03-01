/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 13:35:13 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/01 15:29:05 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>

# include "libft.h"

typedef struct s_ipos
{
	int		x;
	int		y;
}			t_ipos;

typedef struct s_dpos
{
	double	x;
	double	y;
}			t_dpos;

typedef struct s_map
{
	t_ipos	dimensions;
	char	**map;
	char	*textures[4];
	int		ceiling;
	int		floor;
}			t_map;

typedef struct s_cub3d
{
	t_map	map;
}			t_cub3d;

// cleanup.c
int		cleanup(t_cub3d *cub3d, int exit_code);

// map.c
bool	parse_map(t_cub3d *cub3d, const char *map);

#endif