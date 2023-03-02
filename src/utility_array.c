/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility_array.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 13:48:06 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/02 14:00:38 by jde-groo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	array_len(char **array)
{
	int	index;

	index = 0;
	if (!array)
		return (index);
	while (array[index])
		index++;
	return (index);
}

int	array_free(char **array)
{
	int	index;

	index = 0;
	if (!array)
		return (0);
	while (array[index])
		free(array[index++]);
	free(array);
	return (0);
}
