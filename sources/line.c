/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 03:29:38 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/13 06:59:01 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	low_slope(mlx_image_t *fdf, t_dot d0, t_dot d1, int yi)
{
	int		dx;
	int		dy;
	int		d;

	dx = d1.sx - d0.sx;
	dy = abs(d1.sy - d0.sy);
	if (d1.sy - d0.sy < 0)
		yi = -1;
	d = (2 * dy) - dx;
	while (d0.sx++ < d1.sx)
	{
		mlx_put_pixel(fdf, d0.sx, d0.sy, d0.color);
		if (d > 0)
		{
			d0.sy = d0.sy + yi;
			d = d + (2 * (dy - dx));
		}
		else
			d = d + 2 * dy;
	}
}

void	high_slope(mlx_image_t *fdf, t_dot d0, t_dot d1, int xi)
{
	int	dx;
	int	dy;
	int	d;

	dx = abs(d1.sx - d0.sx);
	dy = d1.sy - d0.sy;
	if (d1.sx - d0.sx < 0)
		xi = -1;
	d = (2 * dx) - dy;
	while (d0.sy++ < d1.sy)
	{
		mlx_put_pixel(fdf, d0.sx, d0.sy, d0.color);
		if (d > 0)
		{
			d0.sx = d0.sx + xi;
			d = d + (2 * (dx - dy));
		}
		else
			d = d + 2 * dx;
	}
}

void	draw_line(mlx_image_t *fdf, t_dot *d0, t_dot *d1)
{
	mlx_put_pixel(fdf, d0->sx, d0->sy, d0->color);
	mlx_put_pixel(fdf, d1->sx, d1->sy, d1->color);
	if (abs(d1->sy - d0->sy) < abs(d1->sx - d0->sx))
	{
		if (d0->sx > d1->sx)
			low_slope(fdf, *d1, *d0, 1);
		else
			low_slope(fdf, *d0, *d1, 1);
	}
	else
	{
		if (d0->sy > d1->sy)
			high_slope(fdf, *d1, *d0, 1);
		else
			high_slope(fdf, *d0, *d1, 1);
	}
}
