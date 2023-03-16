/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utility_array.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jde-groo <jde-groo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 13:48:06 by jde-groo      #+#    #+#                 */
/*   Updated: 2023/03/16 13:25:57 by jde-groo      ########   odam.nl         */
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

bool	check_if_there_are_two_commas(char *str)
{
	int	index;
	int	commas;

	index = 0;
	commas = 0;
	while (str && str[index])
	{
		if (str[index] == ',')
			commas++;
		index++;
	}
	return (commas == 2);
}
