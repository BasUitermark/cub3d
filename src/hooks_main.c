/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: buiterma <buiterma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/04 16:55:03 by buiterma      #+#    #+#                 */
/*   Updated: 2023/03/10 12:08:46 by buiterma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <GLFW/glfw3.h>

void	new_move(void *param)
{
	t_cub3d		*cub3d;
	t_player	*player;
	int			x;
	int			y;

	cub3d = (t_cub3d *)param;
	player = &cub3d->player;
	mlx_get_mouse_pos(cub3d->mlx, &x, &y);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub3d->mlx);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W) || \
		mlx_is_key_down(cub3d->mlx, MLX_KEY_S) || \
		mlx_is_key_down(cub3d->mlx, MLX_KEY_A) || \
		mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		execute_strafe(cub3d, player);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT) || \
		mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT) || \
		x != player->mouse.x)
		execute_pan(cub3d, player);
	test(cub3d);
}