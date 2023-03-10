/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: buiterma <buiterma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/05 13:02:16 by buiterma      #+#    #+#                 */
/*   Updated: 2023/03/10 17:17:16 by buiterma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	look_left(t_cub3d *cub3d, t_player *player)
{
	double	old_dirx;
	double	old_plane;

	old_dirx = player->direction.x;
	old_plane = player->plane.x;
	player->direction.x = player->direction.x * cos(-cub3d->rotSpeed) - \
						player->direction.y * sin(-cub3d->rotSpeed);
	player->direction.y = old_dirx * sin(-cub3d->rotSpeed) + \
						player->direction.y * cos(-cub3d->rotSpeed);
	player->plane.x = player->plane.x * cos(-cub3d->rotSpeed) - \
					player->plane.y * sin(-cub3d->rotSpeed);
	player->plane.y = old_plane * sin(-cub3d->rotSpeed) + \
					player->plane.y * cos(-cub3d->rotSpeed);
}

void	look_right(t_cub3d *cub3d, t_player *player)
{
	double	old_dirx;
	double	old_plane;

	old_dirx = player->direction.x;
	old_plane = player->plane.x;
	player->direction.x = player->direction.x * cos(cub3d->rotSpeed) - \
						player->direction.y * sin(cub3d->rotSpeed);
	player->direction.y = old_dirx * sin(cub3d->rotSpeed) + \
						player->direction.y * cos(cub3d->rotSpeed);
	player->plane.x = player->plane.x * cos(cub3d->rotSpeed) - \
					player->plane.y * sin(cub3d->rotSpeed);
	player->plane.y = old_plane * sin(cub3d->rotSpeed) + \
					player->plane.y * cos(cub3d->rotSpeed);
}

void	key_move(t_cub3d *cub3d, t_player *player)
{
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		look_left(cub3d, player);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		look_right(cub3d, player);
}

void	mouse_move(t_cub3d *cub3d, t_player *player, int *cur_x)
{
	double	old_dirx;
	double	old_plane;

	old_dirx = player->direction.x;
	old_plane = player->plane.x;
	if (mlx_get_time() < 0.5)
		return (mlx_set_mouse_pos(cub3d->mlx, WIDTH / 2, HEIGHT / 2));
	if (*cur_x < player->mouse.x && *cur_x != player->mouse.x)
		look_left(cub3d, player);
	if (*cur_x > player->mouse.x && *cur_x != player->mouse.x)
		look_right(cub3d, player);
}

void	execute_pan(t_cub3d *cub3d, t_player *player)
{
	int		cur_x;
	int		cur_y;

	mlx_get_mouse_pos(cub3d->mlx, &cur_x, &cur_y);
	cub3d->rotSpeed = ft_linear_conversion(player->input_range, \
		player->output_range, ft_abs(player->mouse.x - cur_x));
	key_move(cub3d, player);
	mouse_move(cub3d, player, &cur_x);
	cur_x = WIDTH / 2;
	player->mouse.x = cur_x;
	mlx_set_mouse_pos(cub3d->mlx, WIDTH / 2, HEIGHT / 2);
}
