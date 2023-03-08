/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raytrace.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 11:42:13 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/08 17:13:59 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ray_setup(int x, t_ray *ray, t_player *player)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->direction.x = player->direction.x + player->plane.x \
		* ray->camera_x;
	ray->direction.y = player->direction.y + player->plane.y \
		* ray->camera_x;
	ray->player_loc.x = (int)player->location.x;
	ray->player_loc.y = (int)player->location.y;
	ray->delta_dist.x = 1e30;
	ray->delta_dist.y = 1e30;
	if (ray->direction.x != 0)
		ray->delta_dist.x = fabs(1 / ray->direction.x);
	if (ray->direction.y != 0)
		ray->delta_dist.y = fabs(1 / ray->direction.y);
}

static void	calc_step(t_ray *ray, t_player *player)
{
	if (ray->direction.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->location.x - ray->player_loc.x) \
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->player_loc.x + 1.0 - player->location.x) \
			* ray->delta_dist.x;
	}
	if (ray->direction.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->location.y - ray->player_loc.y) \
			*ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->player_loc.y + 1.0 - player->location.y) \
			*ray->delta_dist.y;
	}
}

static void	dda(t_ray *ray, t_map *map)
{
	while (true)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->player_loc.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->player_loc.y += ray->step.y;
			ray->side = 1;
		}
		if (map->map[ray->player_loc.y][ray->player_loc.x] == '1')
			break ;
	}
}

static void	calc_misc(t_ray *ray, t_player *player)
{
	double	pwall_dist;

	pwall_dist = ray->side_dist.x - ray->delta_dist.x;
	if (ray->side)
		pwall_dist = ray->side_dist.y - ray->delta_dist.y;
	ray->line.x = -((int)(HEIGHT / pwall_dist)) / 2 + HEIGHT / 2;
	ray->line.y = ((int)(HEIGHT / pwall_dist)) / 2 + HEIGHT / 2;
	ray->wall_x = player->location.y + pwall_dist * ray->direction.y;
	if (ray->side)
		ray->wall_x = player->location.x + pwall_dist * ray->direction.x;
	ray->wall_x -= floor(ray->wall_x);
	if (!ray->side && ray->direction.x >= 0)
		ray->side = 1;
	else if (!ray->side && ray->direction.x < 0)
		ray->side = 3;
	else if (ray->side && ray->direction.y >= 0)
		ray->side = 2;
	else
		ray->side = 0;
	if (ray->side > 1)
		ray->wall_x = 1.0 - ray->wall_x;
}

void	raytrace(int x, t_ray *ray, t_cub3d *cub3d)
{
	t_map		*map;
	t_player	*player;

	map = &cub3d->map;
	player = &cub3d->player;
	ray_setup(x, ray, player);
	calc_step(ray, player);
	dda(ray, map);
	calc_misc(ray, player);
}
