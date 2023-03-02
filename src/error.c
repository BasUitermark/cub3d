/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 14:49:26 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/02 15:46:20 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	perr(const char *error, int ret)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd((char *)error, STDERR_FILENO);
	return (ret);
}
