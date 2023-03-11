/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 13:26:25 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/11 20:18:23 by buiterma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_line(t_ray *ray, mlx_image_t *image, \
	mlx_texture_t *texture, int w)
{
	t_ipos	oc;
	t_ipos	heights;
	t_ipos	pixel_location;
	int		index;

	oc.x = 0;
	heights.y = ray->line.y - ray->line.x;
	if (heights.y > HEIGHT)
		oc.x = (heights.y - HEIGHT) / 2;
	heights.x = ray->line.y - ray->line.x;
	if (heights.x >= HEIGHT)
		heights.x = HEIGHT - 1;
	pixel_location.x = (int)((texture->width) * ray->wall_x);
	index = 0;
	while (index < heights.x)
	{
		pixel_location.y = (int)((((float)texture->height \
			/ heights.y)) * (index + oc.x));
		oc.y = *(int *)(&texture->pixels[(pixel_location.y * texture->width \
			+ pixel_location.x) * sizeof(int)]);
		oc.y = ((oc.y >> 24) & 0xff) | ((oc.y << 8) & 0xff0000) | \
			((oc.y >> 8) & 0xff00) | ((oc.y << 24) & 0xff000000);
		mlx_put_pixel(image, w, (HEIGHT - heights.x - 1) / 2 + index, oc.y);
		index++;
	}
}

void	test(t_cub3d *cub3d)
{
	t_ray	ray;
	int		index;

	mlx_delete_image(cub3d->mlx, cub3d->foreground);
	cub3d->foreground = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->foreground)
		exit(cleanup(cub3d, EXIT_FAILURE));
	index = 0;
	while (index < WIDTH)
	{
		raytrace(index, &ray, cub3d);
		draw_line(&ray, cub3d->foreground, cub3d->textures[ray.side], index);
		index++;
	}
	mlx_image_to_window(cub3d->mlx, cub3d->foreground, 0, 0);
}

void	init_plane_speed(t_cub3d *cub3d)
{
	mlx_set_cursor_mode(cub3d->mlx, 0x00034002);
	cub3d->mov_speed = 0.04;
	cub3d->rot_speed = 0.05;
	cub3d->player.input_range.x = 0;
	cub3d->player.input_range.y = 1000;
	cub3d->player.output_range.x = 0.015;
	cub3d->player.output_range.y = 0.5;
}

int	main(const int argc, const char *argv[])
{
	t_cub3d		cub3d;

	ft_memset(&cub3d, 0, sizeof(t_cub3d));
	if (argc != 2)
		return ((printf(BOLD "usage: ./cub3d <map>\n" RESET) & 0) | \
		EXIT_FAILURE);
	if (!parse_map(&cub3d, argv[1]) || \
		!validate_map(&cub3d) || \
		!load_textures(&cub3d) || \
		!setup(&cub3d))
		return (cleanup(&cub3d, EXIT_FAILURE));
	init_plane_speed(&cub3d);
	if (mlx_image_to_window(cub3d.mlx, cub3d.background, 0, 0) < 0 ||
		mlx_loop_hook(cub3d.mlx, &new_move, &cub3d) == false)
		return (cleanup(&cub3d, EXIT_FAILURE));
	mlx_loop(cub3d.mlx);
	return (cleanup(&cub3d, EXIT_SUCCESS));
}
