/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:58:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/11 14:53:57 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_dot	**map;
	int		y_index;
	int		x_index;

	map = buil_map_arrays(argv[1]);
	if (map == NULL)
		return (1);
	y_index = 0;
	while (map[y_index])
	{
		x_index = 0;
		while (map[y_index][x_index].color != 0)
		{
			printf("%i,%i,%i,/%lx\n", x_index + 1, y_index + 1, map[y_index][x_index].z, map[y_index][x_index].color);
			x_index++;
		}
		printf("\n");
		y_index++;
	}
	free_map(map, 0);
	(void) argc;
}
