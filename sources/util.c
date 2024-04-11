/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:50:23 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/11 14:54:08 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Finds the number of dots in the line.
 * 
 * @param line Line containing the dots
 * @retval Number of dots in the line.
 */
int	find_x(char *line)
{
	int	index;
	int	x;

	index = 0;
	x = 0;
	while (line[index] && my_isspace(line[index]) != 0)
		index++;
	while (line[index])
	{
		x++;
		while (line[index] && my_isspace(line[index]) == 0)
			index++;
		while (line[index] && my_isspace(line[index]) != 0)
			index++;
	}
	return (x);
}

/**
 * @brief Modified version of ft_atoi that uses an int pointer as index
 * 
 * @param str Str to convert to an integers.
 * @param index Index to where to start converting from.
 * @retval The str converted to an integer
 */
int	fdf_atoi(const char *str, int *index)
{
	int		sign;
	int		num;

	sign = 1;
	num = 0;
	while (my_isspace(str[*index]))
		(*index)++;
	if (str[*index] == '-')
		sign = -1;
	if (str[*index] == '+' || str[*index] == '-')
		(*index)++;
	while (str[*index] && (ft_isdigit(str[*index])))
	{
		num = num * 10 + (str[*index] - 48) * sign;
		(*index)++;
	}
	return (num);
}

/**
 * @brief Frees the map array and it's sub arrays.
 * 
 * @param map 3D array to be freed.
 * @param index Index to start freeing from.
 */
void	free_map(t_dot	**map, int index)
{
	while (map && map[index])
	{
		free(map[index++]);
	}
	free(map);
}
