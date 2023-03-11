/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: buiterma <buiterma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/05 13:02:16 by buiterma      #+#    #+#                 */
/*   Updated: 2023/03/11 12:46:28 by buiterma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double ft_linear_conversion_old(double old[2], double new[2], double old_value)
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
	mlx_set_cursor_mode(cub3d->mlx, 0x00034002);
	
	// printf(BLUE BOLD "Diff linear: %f\n" RESET, ft_linear_conversion_old(old_range, new_range, ft_abs(player->mouse.x - cur_x)));
	// printf(GREEN BOLD "Diff: %d\n" RESET, ft_abs(player->mouse.x - cur_x));
	
	cub3d->rotSpeed = ft_linear_conversion_old(old_range, new_range, ft_abs(player->mouse.x - cur_x));

	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub3d->mlx);
	//left and right key
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->direction.x;
		player->direction.x = player->direction.x * cos(-cub3d->rotSpeed) - player->direction.y * sin(-cub3d->rotSpeed);
		player->direction.y = oldDirX * sin(-cub3d->rotSpeed) + player->direction.y * cos(-cub3d->rotSpeed);
		double oldPlane = player->plane.x;
		player->plane.x = player->plane.x * cos(-cub3d->rotSpeed) - player->plane.y * sin(-cub3d->rotSpeed);
		player->plane.y = oldPlane * sin(-cub3d->rotSpeed) + player->plane.y * cos(-cub3d->rotSpeed);
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->direction.x;
		player->direction.x = player->direction.x * cos(cub3d->rotSpeed) - player->direction.y * sin(cub3d->rotSpeed);
		player->direction.y = oldDirX * sin(cub3d->rotSpeed) + player->direction.y * cos(cub3d->rotSpeed);
		double oldPlane = player->plane.x;
		player->plane.x = player->plane.x * cos(cub3d->rotSpeed) - player->plane.y * sin(cub3d->rotSpeed);
		player->plane.y = oldPlane * sin(cub3d->rotSpeed) + player->plane.y * cos(cub3d->rotSpeed);
	}
	//mouse movement
	// only track if mouse is being moved
	if (cur_x != player->mouse.x)
	{
		if (cur_x < player->mouse.x)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = player->direction.x;
			player->direction.x = player->direction.x * cos(-cub3d->rotSpeed) - player->direction.y * sin(-cub3d->rotSpeed);
			player->direction.y = oldDirX * sin(-cub3d->rotSpeed) + player->direction.y * cos(-cub3d->rotSpeed);
			double oldPlane = player->plane.x;
			player->plane.x = player->plane.x * cos(-cub3d->rotSpeed) - player->plane.y * sin(-cub3d->rotSpeed);
			player->plane.y = oldPlane * sin(-cub3d->rotSpeed) + player->plane.y * cos(-cub3d->rotSpeed);
		}
		else if (cur_x > player->mouse.x)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = player->direction.x;
			player->direction.x = player->direction.x * cos(cub3d->rotSpeed) - player->direction.y * sin(cub3d->rotSpeed);
			player->direction.y = oldDirX * sin(cub3d->rotSpeed) + player->direction.y * cos(cub3d->rotSpeed);
			double oldPlane = player->plane.x;
			player->plane.x = player->plane.x * cos(cub3d->rotSpeed) - player->plane.y * sin(cub3d->rotSpeed);
			player->plane.y = oldPlane * sin(cub3d->rotSpeed) + player->plane.y * cos(cub3d->rotSpeed);
		}
	}
	mlx_set_mouse_pos(cub3d->mlx, WIDTH / 2, HEIGHT / 2);
	// reset mouse back to center
	cur_x = WIDTH / 2;
	player->mouse.x = cur_x;
	cub3d->rotSpeed = 0.05;
}
