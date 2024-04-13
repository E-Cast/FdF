/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 03:29:38 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/13 09:37:17 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	get_fraction(float x1, float x2, float x)
{
	if (x1 != x2)
		return ((x - x1) / (x2 - x1));
	return (0);
}

size_t	gradient(t_dot index, t_dot strt, t_dot dest)
{
	int		dx;
	int		dy;
	float	fraction;
	int		rgba[4];

	dx = dest.x - strt.sx;
	dy = dest.y - strt.sy;
	if (abs(dx) > abs(dy))
		fraction = get_fraction(strt.sx, dest.sx, index.sx);
	else
		fraction = get_fraction(strt.sy, dest.sy, index.sy);
	rgba[0] = (strt.color >> 24 & 0xFF) + ((dest.color >> 24 & 0xFF)
			- (strt.color >> 24 & 0xFF)) * fraction;
	rgba[1] = (strt.color >> 16 & 0xFF) + ((dest.color >> 16 & 0xFF)
			- (strt.color >> 16 & 0xFF)) * fraction;
	rgba[2] = (strt.color >> 8 & 0xFF) + ((dest.color >> 8 & 0xFF)
			- (strt.color >> 8 & 0xFF)) * fraction;
	rgba[3] = (strt.color & 0xFF) + ((dest.color & 0xFF)
			- (strt.color & 0xFF)) * fraction;
	return (rgba[0] << 24 | rgba[1] << 16 | rgba[2] << 8 | rgba[3]);
}

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
 * @brief Draw a line of pixels connecting start and dest.
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
