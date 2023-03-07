/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 14:49:26 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/04 10:36:27 by buiterma      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	perr(const char *error, int ret)
{
	ft_putstr_fd(RED BOLD "Error:\n" RESET, STDERR_FILENO);
	ft_putstr_fd((char *)error, STDERR_FILENO);
	return (ret);
}
