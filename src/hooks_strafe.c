/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks_strafe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: buiterma <buiterma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/04 17:05:43 by buiterma      #+#    #+#                 */
/*   Updated: 2023/03/07 16:46:18 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	strafe_forward(t_cub3d *cub3d, t_player *player)
{
	if (is_valid_location(player->location.x + player->direction.x * \
		cub3d->movSpeed, 0, cub3d))
		player->location.x += player->direction.x * cub3d->movSpeed;
	if (is_valid_location(0, player->location.y + player->direction.y * \
		cub3d->movSpeed, cub3d))
		player->location.y += player->direction.y * cub3d->movSpeed;
}

static void	strafe_backward(t_cub3d *cub3d, t_player *player)
{
	if (is_valid_location(player->location.x - player->direction.x * \
		cub3d->movSpeed, 0, cub3d))
		player->location.x -= player->direction.x * cub3d->movSpeed;
	if (is_valid_location(0, player->location.y - player->direction.y * \
		cub3d->movSpeed, cub3d))
		player->location.y -= player->direction.y * cub3d->movSpeed;
}

static void	strafe_left(t_cub3d *cub3d, t_player *player)
{
	if (is_valid_location(player->location.x + player->direction.y * \
		cub3d->movSpeed, 0, cub3d))
		player->location.x += player->direction.y * cub3d->movSpeed;
	if (is_valid_location(0, player->location.y + -player->direction.x * \
		cub3d->movSpeed, cub3d))
		player->location.y += -player->direction.x * cub3d->movSpeed;
}

static void	strafe_right(t_cub3d *cub3d, t_player *player)
{
	if (is_valid_location(player->location.x + -player->direction.y * \
		cub3d->movSpeed, 0, cub3d))
		player->location.x += -player->direction.y * cub3d->movSpeed;
	if (is_valid_location(0, player->location.y + player->direction.x * \
		cub3d->movSpeed, cub3d))
		player->location.y += player->direction.x * cub3d->movSpeed;
}

void	execute_strafe(t_cub3d *cub3d, t_player *player)
{
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		strafe_forward(cub3d, player);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		strafe_backward(cub3d, player);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		strafe_left(cub3d, player);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		strafe_right(cub3d, player);
}
