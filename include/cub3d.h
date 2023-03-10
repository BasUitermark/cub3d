/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 13:35:13 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/10 17:11:50 by buiterma      ########   odam.nl         */
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

# include "../libs/libft/include/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

# define WIDTH 	1920
# define HEIGHT 1080

typedef struct s_ipos
{
	int				x;
	int				y;
}					t_ipos;

// typedef struct s_dpos
// {
// 	double			x;
// 	double			y;
// }					t_dpos;

typedef struct s_player
{
	t_dpos			location;
	t_dpos			direction;
	t_dpos			plane;
	t_ipos			mouse;
	t_ipos			mouse_new;
	t_dpos			input_range;
	t_dpos			output_range;
}					t_player;

typedef struct s_map
{
	t_ipos			dimensions;
	char			**raw_map;
	char			**map;
	char			*textures[4];
	int				ceiling;
	int				floor;
}					t_map;

typedef struct s_cub3d
{
	t_map			map;
	mlx_t			*mlx;
	mlx_texture_t	*textures[4];
	mlx_image_t		*background;
	mlx_image_t		*foreground;
	mlx_image_t		*mini_map;
	t_player		player;
	t_dpos			plane;
	double			movSpeed;
	double			rotSpeed;
}					t_cub3d;

// error.c
int		perr(const char *error, int ret);

// utility_array.c
int		array_len(char **array);
int		array_free(char **array);

// utility_map.c
char	**read_map(const char *map);

// cleanup.c
int		cleanup(t_cub3d *cub3d, int exit_code);

// map_parsing.c
bool	parse_map(t_cub3d *cub3d, const char *map);

// map_validating.c
bool	validate_map(t_cub3d *cub3d);

// textures.c
bool	load_textures(t_cub3d *cub3d);

// graphics_setup.c
bool	setup(t_cub3d *cub3d);

// hooks_main.c
void	new_move(void *param);

/**
 * @brief Check if next player position hits wall or map bounds
 * 
 * @param cub3d 
 * @param player 
 */
bool	is_valid_location(double x, double y, t_cub3d *cub3d);
bool	is_valid_location_new(double x, double y, t_cub3d *cub3d);


void	execute_strafe(t_cub3d *cub3d, t_player *player);
void	execute_pan(t_cub3d *cub3d, t_player *player);

void	test(t_cub3d *cub3d);

#endif