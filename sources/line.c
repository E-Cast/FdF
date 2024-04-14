/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 03:29:38 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/14 01:57:04 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Draws a horizontally inclined line of pixels
 *  connecting the start and dest dots.
 * 
 * @param fdf Image to draw the pixels on.
 * @param index Dot struct used as index.
 * @param start Starting dot.
 * @param dest Destination dot.
 */
void	low_slope(mlx_image_t *fdf, t_dot index, t_dot start, t_dot dest)
{
	int		dx;
	int		dy;
	int		d;
	int		yi;

	dx = dest.sx - start.sx;
	dy = abs(dest.sy - start.sy);
	yi = 1;
	if (dest.sy - start.sy < 0)
		yi = -1;
	d = (2 * dy) - dx;
	while (index.sx++ < dest.sx)
	{
		mlx_put_pixel(fdf, index.sx, index.sy, gradient(index, start, dest));
		if (d > 0)
		{
			index.sy = index.sy + yi;
			d = d + (2 * (dy - dx));
		}
		else
			d = d + 2 * dy;
	}
}

/**
 * @brief Draws a vertically inclined line of pixels
 *  connecting the start and dest dots.
 * 
 * @param fdf Image to draw the pixels on.
 * @param index Dot struct used as index.
 * @param start Starting dot.
 * @param dest Destination dot.
 */
void	high_slope(mlx_image_t *fdf, t_dot index, t_dot start, t_dot dest)
{
	int	dx;
	int	dy;
	int	d;
	int	xi;

	dx = abs(dest.sx - start.sx);
	dy = dest.sy - start.sy;
	xi = 1;
	if (dest.sx - start.sx < 0)
		xi = -1;
	d = (2 * dx) - dy;
	while (index.sy++ < dest.sy)
	{
		mlx_put_pixel(fdf, index.sx, index.sy, gradient(index, start, dest));
		if (d > 0)
		{
			index.sx = index.sx + xi;
			d = d + (2 * (dx - dy));
		}
		else
			d = d + 2 * dx;
	}
}

/**
 * @brief Draws a line of pixels connecting start and dest.
 * 
 * @param fdf Image to draw the pixels on.
 * @param start Starting dot.
 * @param dest Destination dot.
 */
void	draw_line(mlx_image_t *fdf, t_dot *start, t_dot *dest)
{
	mlx_put_pixel(fdf, start->sx, start->sy, start->color);
	mlx_put_pixel(fdf, dest->sx, dest->sy, dest->color);
	if (abs(dest->sy - start->sy) < abs(dest->sx - start->sx))
	{
		if (start->sx > dest->sx)
			low_slope(fdf, *dest, *dest, *start);
		else
			low_slope(fdf, *start, *start, *dest);
	}
	else
	{
		if (start->sy > dest->sy)
			high_slope(fdf, *dest, *dest, *start);
		else
			high_slope(fdf, *start, *start, *dest);
	}
}

/**
 * @brief Draws lines connecting every dot by using the draw_line function.
 * 
 * @param fdf Image to draw the pixels on.
 * @param map 2D array containing every dot.
 */
void	draw_all(mlx_image_t *fdf, t_dot ***map)
{
	int	x_indx;
	int	y_indx;

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
