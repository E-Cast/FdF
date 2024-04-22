/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:58:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/22 06:09:24 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_params	init_params(int argc, char **argv)
{
	t_params	params;


	params.scale = DEFAULT_SCALE;
	if (argc >= 3)
		params.scale = ft_atoi(argv[2]);
	params.angle = DEFAULT_ANGLE;
	params.window_width = DEFAULT_WIDTH;
	params.window_height = DEFAULT_HEIGHT;
	if (argc >= 4)
	{
		params.window_width = ft_atoi(argv[3]);
		if (ft_strchr(argv[3], ','))
			if (ft_isdigit(*ft_strchr(argv[3], ',') + 1))
				ft_atoi(ft_strchr(argv[3], ',') + 1);
	}
	params.color[0] = DEFAULT_COLOR;
	params.color[1] = DEFAULT_ALPHA;
	return (params);
}

void	update_dot(t_dot *dot, t_params *params)
{
	dot->sx = (dot->x - dot->y) * params->scale * cos(params->angle);
	dot->sy = (dot->x + dot->y) * params->scale * sin(params->angle)
		- dot->z * params->scale;
	dot->sx += (params->window_width / 100 * 80) / 2;
	dot->sy += params->window_height / 4;
	// dot->sx += params->window_width / 2;
	// dot->sy += params->window_height / 2;
}

void	update_map(t_dot ***map, t_params *params)
{
	int	x_indx;
	int	y_indx;

	y_indx = 0;
	while (map[y_indx])
	{
		x_indx = 0;
		while (map[y_indx][x_indx])
			update_dot(map[y_indx][x_indx++], params);
		y_indx++;
	}
}

int	main(int argc, char **argv)
{
	t_dot		***map;
	t_params	params;

	if (argc < 2 || argc > 4)
	{
		ft_putendl_fd("Format: <filename> [SCALE] [RES]", STDERR_FILENO);
		ft_putendl_fd("E.G: ./fdf map.txt 10 1280,720", STDERR_FILENO);
		return (1);
	}
	params = init_params(argc, argv);
	map = build_map(argv[1], params.color);
	if (map == NULL)
		return (ft_putendl_fd("Failed to read map.", STDERR_FILENO), 1);
	update_map(map, &params);
	mlx_start(map, &params);
	free_map(map);
}
