/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks_strafe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: buiterma <buiterma@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/04 17:05:43 by buiterma      #+#    #+#                 */
/*   Updated: 2023/03/04 17:19:44 by buiterma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	execute_strafe(t_cub3d *cub3d, t_player *player)
{
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
	{
		//check if next player position is over map bounds
		if (is_valid_location(player->location.x + player->direction.x * cub3d->movSpeed, 0, cub3d->map.dimensions))
			player->location.x += player->direction.x * cub3d->movSpeed;
		if (is_valid_location(0, player->location.y + player->direction.y * cub3d->movSpeed, cub3d->map.dimensions))
			player->location.y += player->direction.y * cub3d->movSpeed;

	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
	{
		//check if next player position is over map bounds
		if (is_valid_location(player->location.x - player->direction.x * cub3d->movSpeed, 0, cub3d->map.dimensions))
			player->location.x -= player->direction.x * cub3d->movSpeed;
		if (is_valid_location(0, player->location.y - player->direction.y * cub3d->movSpeed, cub3d->map.dimensions))
			player->location.y -= player->direction.y * cub3d->movSpeed;
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
	{
		//check if next player position is over map bounds
		if (is_valid_location(player->location.x + -player->direction.y * cub3d->movSpeed, 0, cub3d->map.dimensions))
			player->location.x += -player->direction.y * cub3d->movSpeed;
		if (is_valid_location(0, player->location.y + player->direction.x * cub3d->movSpeed, cub3d->map.dimensions))
			player->location.y += player->direction.x * cub3d->movSpeed;

	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
	{
		//check if next player position is over map bounds
		if (is_valid_location(player->location.x + player->direction.y * cub3d->movSpeed, 0, cub3d->map.dimensions))
			player->location.x += player->direction.y * cub3d->movSpeed;
		if (is_valid_location(0, player->location.y + -player->direction.x * cub3d->movSpeed, cub3d->map.dimensions))
			player->location.y += -player->direction.x * cub3d->movSpeed;
	}
}