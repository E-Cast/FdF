/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:58:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/15 18:16:27 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mods	init_mods(int argc, char **argv)
{
	t_mods	mods;


	mods.xy_scale = XY_SCALE;
	if (argc >= 3)
		mods.xy_scale = ft_atoi(argv[2]);
	mods.z_scale = Z_SCALE;
	if (argc >= 4)
		mods.z_scale = ft_atoi(argv[3]);
	mods.color[0] = DEFAULT_COLOR;
	if (argc >= 5)
		mods.color[0] = my_atoh(argv[4]);
	mods.color[1] = DEFAULT_ALPHA;
	mods.window_width = DEFAULT_WIDTH;
	mods.window_height = DEFAULT_HEIGHT;
	if (argc >= 6)
		mods.window_width = ft_atoi(argv[5]);
	if (argc >= 6)
		mods.window_height = ft_atoi(ft_strchr(argv[5], ',') + 1);
	mods.angle = DEFAULT_ANGLE;
	return (mods);
}

void	update_dot(t_dot *dot, t_mods *mods)
{
	dot->sx = (dot->x - dot->y) * mods->xy_scale * cos(mods->angle);
	dot->sy = (dot->x + dot->y) * mods->xy_scale * sin(mods->angle)
		- dot->z * mods->z_scale;
	dot->sx += (mods->window_width / 100 * 80) / 2;
	dot->sy += mods->window_height / 4;
}

void	update_map(t_dot ***map, t_mods *mods)
{
	int	x_indx;
	int	y_indx;

	y_indx = 0;
	while (map[y_indx])
	{
		x_indx = 0;
		while (map[y_indx][x_indx])
			update_dot(map[y_indx][x_indx++], mods);
		y_indx++;
	}
}

int	main(int argc, char **argv)
{
	t_dot	***map;
	t_mods	mods;

	if (argc < 2 || argc > 6)
	{
		ft_putstr_fd("Format: <filename> [XY_SCALE] [Z_SCALE]", STDERR_FILENO);
		ft_putendl_fd(" [DEF_COLOR] [RESOLUTION]", STDERR_FILENO);
		ft_putendl_fd("E.G: ./fdf map.txt 20 7 0x00BABCFF 1280,720",
			STDERR_FILENO);
		return (1);
	}
	mods = init_mods(argc, argv);
	map = build_map(argv[1], mods.color);
	if (map == NULL)
		return (ft_putendl_fd("Failed to read map.", STDERR_FILENO), 1);
	update_map(map, &mods);
	mlx_start(map, &mods);
	free_map(map);
}
