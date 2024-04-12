/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:58:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/11 23:09:53 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_map(t_dot **map)
{
	int		y_index;
	int		x_index;

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
}

t_data	init_data(int argc, char **argv)
{
	t_data	data;

	data.xy_scale = XY_SCALE;
	data.z_scale = Z_SCALE;
	data.def_color = DEF_COLOR;
	if (argc >= 3)
		data.xy_scale = ft_atoi(argv[2]);
	if (argc >= 4)
		data.z_scale = ft_atoi(argv[3]);
	if (argc == 5)
		data.def_color = my_atoh(argv[4]);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_dot	**map;

	if (argc < 2 || argc > 5)
	{
		ft_putendl_fd("Format: <filename> [XY_SCALE] [Z_SCALE] [DEF_COLOR]",
			STDERR_FILENO);
		return (1);
	}
	data = init_data(argc, argv);
	printf("%i,%i\n%lx\n", data.xy_scale, data.z_scale, data.def_color);
	map = buil_map_arrays(argv[1], &data);
	if (map == NULL)
		return (ft_putendl_fd("Failed to read map.", STDERR_FILENO), 1);
	print_map(map);
	free_map(map, 0);
}
