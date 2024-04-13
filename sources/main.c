/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:58:48 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/13 03:09:38 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// static t_data	init_data(int argc, char **argv)
// {
// 	t_data	data;

// 	data.xy_scale = XY_SCALE;
// 	data.z_scale = Z_SCALE;
// 	data.def_color = DEF_COLOR;
// 	data.angle = DEF_ANGLE;
// 	if (argc >= 3)
// 		data.xy_scale = ft_atoi(argv[2]);
// 	if (argc >= 4)
// 		data.z_scale = ft_atoi(argv[3]);
// 	if (argc == 5)
// 		data.def_color = my_atoh(argv[4]);
// 	return (data);
// }

// void	test_draw_dots(t_data data, t_dot **map, mlx_image_t *img)
// {
// 	ssize_t	y_index;
// 	ssize_t	x_index;
// 	ssize_t	x_pos;
// 	ssize_t	y_pos;

// 	x_pos = ((3 + 1) * data.xy_scale - (3 + 1) * data.xy_scale) * cos(data.angle);
// 	y_pos = ((4 + 1) * data.xy_scale - (3 + 1) * data.xy_scale) * cos(data.angle);
// 	printf("test1:%ld\n\n", y_pos - x_pos);
// 	x_pos = ((4 - 3) * data.xy_scale) * cos(data.angle);
// 	printf("test2:%ld\n\n", x_pos);
// 	y_index = 0;
// 	while (y_index < data.max_y)
// 	{
// 		x_index = 0;
// 		while (x_index < data.max_x)
// 		{
// 			// x_pos = (x_index * data.xy_scale) * cos(data.angle) + (y_index * data.xy_scale) * cos(data.angle + 2) + (map[y_index][x_index].z * data.z_scale) * cos(data.angle - 2);
// 			// y_pos = (x_index * data.xy_scale) * sin(data.angle) + (y_index * data.xy_scale) * sin(data.angle + 2) + (map[y_index][x_index].z * data.z_scale) * sin(data.angle - 2);
// 			// // x_pos = (x_index + 1) * data.xy_scale;
// 			// // y_pos = (y_index + 1) * data.xy_scale;
// 			x_pos = ((x_index + 1) * data.xy_scale - (y_index + 1) * data.xy_scale) * cos(data.angle);
//  			y_pos = ((x_index + 1) * data.xy_scale +  (y_index + 1) * data.xy_scale) * sin(data.angle) - map[y_index][x_index].z * data.z_scale;
// 			printf("sx:%li/sy%li\nx:%li/y:%li\n\n", x_pos, y_pos, x_index + 1, y_index + 1);
// 			// printf("x:%i\ny:%i\nx_pos:%i\ny_pos:%i\n\n", x_index + 1, y_index + 1, x_pos + 200, y_pos + 100);
// 			// if (x_pos > 0 && y_pos > 0)
// 			mlx_put_pixel(img, x_pos + 170, y_pos + 100, map[y_index][x_index].color);
// 			x_index++;
// 		}
// 		y_index++;
// 	}
// }

// void	test(t_data data, t_dot **map)
// {
// 	size_t		width;
// 	size_t		height;
// 	mlx_t		*mlx;
// 	mlx_image_t	*img;

// 	width = (data.max_x + data.max_y) * data.xy_scale;
// 	height = data.max_y * data.xy_scale + data.xy_scale;
// 	// printf("%li\n%li\n", width, height);
// 	mlx = mlx_init(width, height + 230, "Test", true);
// 	if (!mlx)
// 		return ;
// 	img = mlx_new_image(mlx, width, width + 230);
// 	if (!img)
// 		return ;
// 	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
// 		return ;
// 	test_draw_dots(data, map, img);
// 	mlx_loop(mlx);
// 	mlx_delete_image(mlx, img);
// 	mlx_terminate(mlx);
// 	(void) map;
// }

// static void	print_map(t_dot ***map)
// {
// 	int		y_index;
// 	int		x_index;

// 	y_index = 0;
// 	while (map[y_index])
// 	{
// 		x_index = 0;
// 		while (map[y_index][x_index])
// 		{
// 			printf("x:%i/y:%i/z:%i/c:%lx\n",
// 				map[y_index][x_index]->x, map[y_index][x_index]->y, map[y_index][x_index]->z, map[y_index][x_index]->color);
// 			x_index++;
// 		}
// 		printf("\n");
// 		y_index++;
// 	}
// }

t_mods	init_mods(int argc, char **argv)
{
	t_mods	mods;

	mods.xy_scale = XY_SCALE;
	if (argc >= 3)
		mods.xy_scale = ft_atoi(argv[2]);
	mods.z_scale = Z_SCALE;
	if (argc >= 4)
		mods.z_scale = ft_atoi(argv[3]);
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
	if (argc >= 5)
		map = build_map(argv[1], my_atoh(argv[4]));
	else
		map = build_map(argv[1], DEFAULT_COLOR);
	if (map == NULL)
		return (ft_putendl_fd("Failed to read map.", STDERR_FILENO), 1);
	mods = init_mods(argc, argv);
	update_map(map, &mods);
	mlx_start(map, &mods);
	free_map(map);
}
