/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: buiterma <buiterma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/05 13:02:16 by buiterma      #+#    #+#                 */
/*   Updated: 2023/03/10 12:40:42 by buiterma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <GLFW/glfw3.h>

double ft_linear_conversion(double old[2], double new[2], double old_value)
{
	double new_value;
	double old_range;
	double new_range;

	old_range = (old[1] - old[0]);
	new_range = (new[1] - new[0]);
	new_value = (((old_value - old[0]) * new_range) / old_range) + new[0];
	return (new_value);
}

void	key_move(t_cub3d *cub3d, t_player *player)
{
	double oldDirX = player->direction.x;
	double oldPlane = player->plane.x;

	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
	{
		player->direction.x = player->direction.x * cos(-cub3d->rotSpeed) - player->direction.y * sin(-cub3d->rotSpeed);
		player->direction.y = oldDirX * sin(-cub3d->rotSpeed) + player->direction.y * cos(-cub3d->rotSpeed);
		player->plane.x = player->plane.x * cos(-cub3d->rotSpeed) - player->plane.y * sin(-cub3d->rotSpeed);
		player->plane.y = oldPlane * sin(-cub3d->rotSpeed) + player->plane.y * cos(-cub3d->rotSpeed);
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
	{
		player->direction.x = player->direction.x * cos(cub3d->rotSpeed) - player->direction.y * sin(cub3d->rotSpeed);
		player->direction.y = oldDirX * sin(cub3d->rotSpeed) + player->direction.y * cos(cub3d->rotSpeed);
		player->plane.x = player->plane.x * cos(cub3d->rotSpeed) - player->plane.y * sin(cub3d->rotSpeed);
		player->plane.y = oldPlane * sin(cub3d->rotSpeed) + player->plane.y * cos(cub3d->rotSpeed);
	}
}

void	execute_pan(t_cub3d *cub3d, t_player *player)
{
	int		cur_x;
	int		cur_y;
	double	old_range[2] = {0, 1000};
	double	new_range[2] = {0.025, 0.5};
	double oldDirX = player->direction.x;
	double oldPlane = player->plane.x;

	mlx_get_mouse_pos(cub3d->mlx, &cur_x, &cur_y);
	
	cub3d->rotSpeed = ft_linear_conversion(old_range, new_range, ft_abs(player->mouse.x - cur_x));
	if (mlx_get_time() < 0.5)
	{
		mlx_set_mouse_pos(cub3d->mlx, WIDTH / 2, HEIGHT / 2);
		return ;
	}
	if (cur_x < player->mouse.x && cur_x != player->mouse.x)
	{
		//both camera direction and camera plane must be rotated
		player->direction.x = player->direction.x * cos(-cub3d->rotSpeed) - player->direction.y * sin(-cub3d->rotSpeed);
		player->direction.y = oldDirX * sin(-cub3d->rotSpeed) + player->direction.y * cos(-cub3d->rotSpeed);
		player->plane.x = player->plane.x * cos(-cub3d->rotSpeed) - player->plane.y * sin(-cub3d->rotSpeed);
		player->plane.y = oldPlane * sin(-cub3d->rotSpeed) + player->plane.y * cos(-cub3d->rotSpeed);
	}
	else if (cur_x > player->mouse.x && cur_x != player->mouse.x)
	{
		//both camera direction and camera plane must be rotated
		player->direction.x = player->direction.x * cos(cub3d->rotSpeed) - player->direction.y * sin(cub3d->rotSpeed);
		player->direction.y = oldDirX * sin(cub3d->rotSpeed) + player->direction.y * cos(cub3d->rotSpeed);
		player->plane.x = player->plane.x * cos(cub3d->rotSpeed) - player->plane.y * sin(cub3d->rotSpeed);
		player->plane.y = oldPlane * sin(cub3d->rotSpeed) + player->plane.y * cos(cub3d->rotSpeed);
	}
	cur_x = WIDTH / 2;
	player->mouse.x = cur_x;
	mlx_set_mouse_pos(cub3d->mlx, WIDTH / 2, HEIGHT / 2);
}
