/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecastong <ecastong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:10:00 by ecastong          #+#    #+#             */
/*   Updated: 2024/04/13 23:56:39 by ecastong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Calculates how far index is between start 
 * and end and how to mix the colors accordingly.
 * 
 * @param start Start position.
 * @param end Destination position.
 * @param indexx Current position.
 * @retval A float ranging from 0.000 to 1.000, 
 * 0 being x at x1 and 1 being x at x2.
 */
float	get_ratio(t_dot index, t_dot start, t_dot dest)
{
	int		dx;
	int		dy;
	float	mix;

	dx = dest.x - start.sx;
	dy = dest.y - start.sy;
	mix = 0;
	if (abs(dx) > abs(dy))
	{
		if (start.sx != dest.sx)
			mix = ((float)index.sx - (float)start.sx)
				/ ((float)dest.sx - (float)start.sx);
	}
	else
	{
		if (start.sy != dest.sy)
			mix = ((float)index.sy - (float)start.sy)
				/ ((float)dest.sy - (float)start.sy);
	}
	return (mix);
}

void	prep_color(int *rgb, float *res)
{
	res[0] = norm(rgb[0]);
	res[0] = i_comp(res[0]);
	res[1] = norm(rgb[1]);
	res[1] = i_comp(res[1]);
	res[2] = norm(rgb[2]);
	res[2] = i_comp(res[2]);
}

// Function to apply sRGB companding
void	sRGBCompanding(float *rgb, int *res)
{
	res[0] = comp(rgb[0]);
	res[1] = comp(rgb[1]);
	res[2] = comp(rgb[2]);
}

// Main MarkMix function
void	mark_mix(int *rgb1, int *rgb2, float mix, int *result)
{
	float	n1[3];
	float	n2[3];
	float	rgb[3];
	float	brightness;
	float	factor;

	prep_color(rgb1, n1);
	prep_color(rgb2, n2);
	rgb[0] = intrp(n1[0], n2[0], mix);
	rgb[1] = intrp(n1[1], n2[1], mix);
	rgb[2] = intrp(n1[2], n2[2], mix);
	brightness = intrp(pow(n1[0] + n1[1] + n1[2], GAMMA),
			pow(n2[0] + n2[1] + n2[2], GAMMA), mix);
	if ((rgb[0] + rgb[1] + rgb[2]) != 0)
	{
		factor = pow(brightness, 1 / GAMMA) / (rgb[0] + rgb[1] + rgb[2]);
		rgb[0] *= factor;
		rgb[1] *= factor;
		rgb[2] *= factor;
	}
	sRGBCompanding(rgb, result);
}

size_t	gradient(t_dot index, t_dot start, t_dot dest)
{
	int		rgb1[4];
	int		rgb2[4];
	float	mix;
	int		result[4];

	rgb1[0] = ((start.color >> 24) & 0xFF);
	rgb1[1] = ((start.color >> 16) & 0xFF);
	rgb1[2] = ((start.color >> 8) & 0xFF);
	rgb1[3] = (start.color & 0xFF);
	rgb2[0] = ((dest.color >> 24) & 0xFF);
	rgb2[1] = ((dest.color >> 16) & 0xFF);
	rgb2[2] = ((dest.color >> 8) & 0xFF);
	rgb2[3] = (dest.color & 0xFF);
	mix = get_ratio(index, start, dest);
	mark_mix(rgb1, rgb2, mix, result);
	result[3] = rgb1[3] + (rgb2[3] - rgb1[3]) * mix;
	return (result[0] << 24 | result[1] << 16 | result[2] << 8 | result[3]);
}
