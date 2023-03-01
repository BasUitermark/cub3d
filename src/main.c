/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 13:26:25 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/01 16:28:18 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int	main(const int argc, const char *argv[])
{
	t_cub3d		cub3d;

	ft_memset(&cub3d, 0, sizeof(t_cub3d));
	if (argc != 2)
		return ((printf("usage: ./cub3d <map>\n") & 0) | EXIT_FAILURE);
	if (!parse_map(&cub3d, argv[1]))
		return (cleanup(&cub3d, EXIT_FAILURE));

	return (EXIT_SUCCESS);
}
