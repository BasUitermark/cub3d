/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks_strafe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: buiterma <buiterma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/04 17:05:43 by buiterma      #+#    #+#                 */
/*   Updated: 2023/03/07 17:03:30 by buiterma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	strafe_forward(t_cub3d *cub3d, t_player *player)
{
	double	new_x;
	double	new_y;

	new_x = player->location.x + player->direction.x * cub3d->movSpeed;
	new_y = player->location.y + player->direction.y * cub3d->movSpeed;
	if (is_valid_location_new(new_x, player->location.y, cub3d))
		player->location.x += player->direction.x * cub3d->movSpeed;
	if (is_valid_location_new(player->location.x, new_y, cub3d))
		player->location.y += player->direction.y * cub3d->movSpeed;
}

static void	strafe_backward(t_cub3d *cub3d, t_player *player)
{
	// int	x;
	// int	y;

	// x = (int)floor(player->location.x) + cub3d->movSpeed;
	// y = (int)floor(player->location.y) + cub3d->movSpeed;
	// if (cub3d->map.map[y][x] == '1')
	// 	return ;
	if (is_valid_location(player->location.x - player->direction.x * \
		cub3d->movSpeed, 0, cub3d))
		player->location.x -= player->direction.x * cub3d->movSpeed;
	if (is_valid_location(0, player->location.y - player->direction.y * \
		cub3d->movSpeed, cub3d))
		player->location.y -= player->direction.y * cub3d->movSpeed;
}

static void	strafe_left(t_cub3d *cub3d, t_player *player)
{
	// int	x;
	// int	y;

	// x = (int)floor(player->location.x) + cub3d->movSpeed;
	// y = (int)floor(player->location.y) + cub3d->movSpeed;
	// if (cub3d->map.map[y][x] == '1')
	// 	return ;
	if (is_valid_location(player->location.x + -player->direction.y * \
		cub3d->movSpeed, 0, cub3d))
		player->location.x += -player->direction.y * cub3d->movSpeed;
	if (is_valid_location(0, player->location.y + player->direction.x * \
		cub3d->movSpeed, cub3d))
		player->location.y += player->direction.x * cub3d->movSpeed;
}

static void	strafe_right(t_cub3d *cub3d, t_player *player)
{
	// int	x;
	// int	y;

	// x = (int)floor(player->location.x) + cub3d->movSpeed;
	// y = (int)floor(player->location.y) + cub3d->movSpeed;
	// if (cub3d->map.map[y][x] == '1')
	// 	return ;
	if (is_valid_location(player->location.x + player->direction.y * \
		cub3d->movSpeed, 0, cub3d))
		player->location.x += player->direction.y * cub3d->movSpeed;
	if (is_valid_location(0, player->location.y + -player->direction.x * \
		cub3d->movSpeed, cub3d))
		player->location.y += -player->direction.x * cub3d->movSpeed;
}

void	execute_strafe(t_cub3d *cub3d, t_player *player)
{
	// int	x = (int)floor(player->location.x);
	// int	y = (int)floor(player->location.y);

	// printf(GREEN BOLD "Player X: %f/%d\n" RESET, player->location.x, x);
	// printf(BLUE BOLD "Player Y: %f/%d\n" RESET, player->location.y, y);
	// printf(RED BOLD "Map Point: %c\n" RESET, cub3d->map.map[y][x]);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		strafe_forward(cub3d, player);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		strafe_backward(cub3d, player);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		strafe_left(cub3d, player);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		strafe_right(cub3d, player);
}
