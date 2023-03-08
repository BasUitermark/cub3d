/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 13:26:25 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/08 18:12:25 by jde-groo      ########   odam.nl         */
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

	ft_memset(cub3d->foreground->pixels, 0, cub3d->foreground->width \
		* cub3d->foreground->height * sizeof(int));
	index = 0;
	while (index < WIDTH)
	{
		raytrace(index, &ray, cub3d);
		draw_line(&ray, cub3d->foreground, cub3d->textures[ray.side], index);
		index++;
	}
	mlx_image_to_window(cub3d->mlx, cub3d->foreground, 0, 0); // this shit is causing lag ????? how ??????
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
	cub3d.movSpeed = 0.045;
	cub3d.rotSpeed = 0.05;
	mlx_image_to_window(cub3d.mlx, cub3d.background, 0, 0);
	mlx_loop_hook(cub3d.mlx, &new_move, &cub3d);	// (not sure!!!) uses queue which gets really, really big since events constantly fire and it cannot keep up (i think!!)
	mlx_loop(cub3d.mlx);
	return (cleanup(&cub3d, EXIT_SUCCESS));
}
