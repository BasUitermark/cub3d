/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: buiterma <buiterma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/05 13:02:16 by buiterma      #+#    #+#                 */
/*   Updated: 2023/03/08 18:08:54 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// double	*ft_double_pair(double a, double b)
// {
// 	double	pair[2];

// 	pair[0] = a;
// 	pair[1] = b;
// 	return (pair);
// }

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

void	execute_pan(t_cub3d *cub3d, t_player *player)
{
	int		cur_x;
	int		cur_y;
	double	old_range[2] = {0, 1000};
	double	new_range[2] = {0.025, 0.5};

	mlx_get_mouse_pos(cub3d->mlx, &cur_x, &cur_y);
	mlx_set_cursor_mode(cub3d->mlx, 0x00034002);
	
	// printf(BLUE BOLD "Diff linear: %f\n" RESET, ft_linear_conversion(old_range, new_range, ft_abs(player->mouse.x - cur_x)));
	// printf(GREEN BOLD "Diff: %d\n" RESET, ft_abs(player->mouse.x - cur_x));
	
	cub3d->rotSpeed = ft_linear_conversion(old_range, new_range, ft_abs(player->mouse.x - cur_x));

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
	// if (cur_x != player->mouse.x)
	// {
	// 	if (cur_x < player->mouse.x)
	// 	{
	// 		//both camera direction and camera plane must be rotated
	// 		double oldDirX = player->direction.x;
	// 		player->direction.x = player->direction.x * cos(-cub3d->rotSpeed) - player->direction.y * sin(-cub3d->rotSpeed);
	// 		player->direction.y = oldDirX * sin(-cub3d->rotSpeed) + player->direction.y * cos(-cub3d->rotSpeed);
	// 		double oldPlane = player->plane.x;
	// 		player->plane.x = player->plane.x * cos(-cub3d->rotSpeed) - player->plane.y * sin(-cub3d->rotSpeed);
	// 		player->plane.y = oldPlane * sin(-cub3d->rotSpeed) + player->plane.y * cos(-cub3d->rotSpeed);
	// 	}
	// 	else if (cur_x > player->mouse.x)
	// 	{
	// 		//both camera direction and camera plane must be rotated
	// 		double oldDirX = player->direction.x;
	// 		player->direction.x = player->direction.x * cos(cub3d->rotSpeed) - player->direction.y * sin(cub3d->rotSpeed);
	// 		player->direction.y = oldDirX * sin(cub3d->rotSpeed) + player->direction.y * cos(cub3d->rotSpeed);
	// 		double oldPlane = player->plane.x;
	// 		player->plane.x = player->plane.x * cos(cub3d->rotSpeed) - player->plane.y * sin(cub3d->rotSpeed);
	// 		player->plane.y = oldPlane * sin(cub3d->rotSpeed) + player->plane.y * cos(cub3d->rotSpeed);
	// 	}
	// }
	mlx_set_mouse_pos(cub3d->mlx, WIDTH / 2, HEIGHT / 2);
	// reset mouse back to center
	cur_x = WIDTH / 2;
	player->mouse.x = cur_x;
	// cub3d->rotSpeed = 0.05;
}
