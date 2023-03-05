/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: buiterma <buiterma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/05 13:02:16 by buiterma      #+#    #+#                 */
/*   Updated: 2023/03/05 13:22:10 by buiterma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	execute_pan(t_cub3d *cub3d, t_player *player)
{
	int			cur_x;
	int			cur_y;

	mlx_get_mouse_pos(cub3d->mlx, &cur_x, &cur_y);
	mlx_set_cursor_mode(cub3d->mlx, 0x00034002);

	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub3d->mlx);
	//left and right key
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->direction.x;
		player->direction.x = player->direction.x * cos(cub3d->rotSpeed) - player->direction.y * sin(cub3d->rotSpeed);
		player->direction.y = oldDirX * sin(cub3d->rotSpeed) + player->direction.y * cos(cub3d->rotSpeed);
		double oldPlaneX = cub3d->plane.x;
		cub3d->plane.x = cub3d->plane.x * cos(cub3d->rotSpeed) - cub3d->plane.y * sin(cub3d->rotSpeed);
		cub3d->plane.y = oldPlaneX * sin(cub3d->rotSpeed) + cub3d->plane.y * cos(cub3d->rotSpeed);
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
	{
	  //both camera direction and camera plane must be rotated
	  double oldDirX = player->direction.x;
	  player->direction.x = player->direction.x * cos(-cub3d->rotSpeed) - player->direction.y * sin(-cub3d->rotSpeed);
	  player->direction.y = oldDirX * sin(-cub3d->rotSpeed) + player->direction.y * cos(-cub3d->rotSpeed);
	  double oldPlaneX = cub3d->plane.x;
	  cub3d->plane.x = cub3d->plane.x * cos(-cub3d->rotSpeed) - cub3d->plane.y * sin(-cub3d->rotSpeed);
	  cub3d->plane.y = oldPlaneX * sin(-cub3d->rotSpeed) + cub3d->plane.y * cos(-cub3d->rotSpeed);
	}
	//mouse movement
	// only track if mouse is being moved
	if (cur_x != player->mouse.x)
	{
		if (cur_x < player->mouse.x)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = player->direction.x;
			player->direction.x = player->direction.x * cos(cub3d->rotSpeed) - player->direction.y * sin(cub3d->rotSpeed);
			player->direction.y = oldDirX * sin(cub3d->rotSpeed) + player->direction.y * cos(cub3d->rotSpeed);
			double oldPlaneX = cub3d->plane.x;
			cub3d->plane.x = cub3d->plane.x * cos(cub3d->rotSpeed) - cub3d->plane.y * sin(cub3d->rotSpeed);
			cub3d->plane.y = oldPlaneX * sin(cub3d->rotSpeed) + cub3d->plane.y * cos(cub3d->rotSpeed);
		}
		else if (cur_x > player->mouse.x)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = player->direction.x;
			player->direction.x = player->direction.x * cos(-cub3d->rotSpeed) - player->direction.y * sin(-cub3d->rotSpeed);
			player->direction.y = oldDirX * sin(-cub3d->rotSpeed) + player->direction.y * cos(-cub3d->rotSpeed);
			double oldPlaneX = cub3d->plane.x;
			cub3d->plane.x = cub3d->plane.x * cos(-cub3d->rotSpeed) - cub3d->plane.y * sin(-cub3d->rotSpeed);
			cub3d->plane.y = oldPlaneX * sin(-cub3d->rotSpeed) + cub3d->plane.y * cos(-cub3d->rotSpeed);
		}
	}
	mlx_set_mouse_pos(cub3d->mlx, WIDTH/2, HEIGHT/2);
	//reset mouse back to center
	cur_x = WIDTH/2;
	player->mouse.x = cur_x;
}
