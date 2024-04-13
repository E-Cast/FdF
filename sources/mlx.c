/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 01:11:21 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/13 05:38:05 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

mlx_image_t	*make_image(mlx_t *mlx, int width, int height, int start)
{
	mlx_image_t	*fdf;

	fdf = mlx_new_image(mlx, width, height);
	if (!fdf)
		return (NULL);
	if (mlx_image_to_window(mlx, fdf, start, 0) < 0)
		return (mlx_delete_image(mlx, fdf), NULL);
	return (fdf);
}

void	draw_all(t_dot ***map, mlx_image_t *fdf)
{
	int		x_indx;
	int		y_indx;

	y_indx = 0;
	while (map[y_indx])
	{
		x_indx = 0;
		while (map[y_indx][x_indx])
		{
			if (map[y_indx][x_indx + 1])
				draw_line(fdf, map[y_indx][x_indx], map[y_indx][x_indx + 1]);
			if (map[y_indx + 1])
				draw_line(fdf, map[y_indx + 1][x_indx], map[y_indx][x_indx]);
			x_indx++;
		}
		y_indx++;
	}
}

int	mlx_start(t_dot ***map, t_mods *mods)
{
	mlx_t		*mlx;
	mlx_image_t	*fdf_img;
	mlx_image_t	*ui_img;
	int			fdf_width;
	int			ui_width;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	fdf_width = mods->window_width / 100 * 80;
	ui_width = mods->window_width - fdf_width;
	mlx = mlx_init(mods->window_width, mods->window_height, "FdF", true);
	if (!mlx)
		return (EXIT_FAILURE);
	fdf_img = make_image(mlx, fdf_width, mods->window_height, ui_width);
	if (!fdf_img)
		return (EXIT_FAILURE);
	ui_img = make_image(mlx, ui_width, mods->window_height, 0);
	if (!ui_img)
		return (EXIT_FAILURE);
	ft_memset(ui_img->pixels, 150, ui_width * mods->window_height * sizeof(int));
	draw_all(map, fdf_img);
	mlx_loop(mlx);
	mlx_delete_image(mlx, fdf_img);
	mlx_delete_image(mlx, ui_img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
	(void) map;
}
